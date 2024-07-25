#include "PezGlobo.h"


PezGlobo::PezGlobo() : Enemigo() {}

PezGlobo::~PezGlobo() {}

void PezGlobo::update(float deltaTime, const std::vector<std::vector<int>>& map) {
    this->deltaTime = deltaTime;
    detectarPiso(map, this->PISO);
    detectarTecho(map);
    if (!verificarMoverseMismaPlataforma) {
        detectarObjDer(map);
        detectarObjIzq(map);
    }
    verificarColisionBalaBloque();
    applyGravity();
    //controlarMovimientoHorizontal(deltaTime);
    controlarMovimientoVertical();
    moverHorizontalSprite(left, right);
    disparar();
    
    for (auto& bala : balas) {
        bala->update(deltaTime, map);
    }
    verificarTiempoVidaBalas();
}

void PezGlobo::disparar() {
    float tiempoIntervaloBala = relojIntervaloBala.getElapsedTime().asSeconds();
    if (tiempoIntervaloBala > 3.0f) {
        balas.push_back(std::make_unique<Bala>(getPosX() + anchoHitbox / 2, getPosY() + altoHitbox / 2, vistaIzq));
        relojIntervaloBala.restart();   
    }
    
    float tiempoMovimientoDireccion = relojMovimientoDireccion.getElapsedTime().asSeconds();
    if (tiempoMovimientoDireccion > 6.0f) {
        vistaIzq = !vistaIzq;
        relojMovimientoDireccion.restart();
    }
}

void PezGlobo::verificarColisionBalaGato(Gato& gato) {
    for (int i = 0; i < balas.size(); i++) {
        if (gato.getHitBox().getGlobalBounds().intersects(balas[i]->getHitBox().getGlobalBounds())) {
            gato.morir();
        }
    }
}


void PezGlobo::verificarColisionBalaBloque() {
    for (int i = 0; i < balas.size(); i++) {
        if (balas.at(i)->getPosX() + anchoHitbox > OBJDER) {
            balas.erase(balas.begin() + i);
        }

        else if (getPosX() < OBJIZQ) {
            balas.erase(balas.begin() + i);
        }
    }
}

void PezGlobo::verificarTiempoVidaBalas() {
    for (int i = 0; i < balas.size(); i++) {
        if (balas.at(i)->verificarTiempoVida()) {
            balas.erase(balas.begin() + i);
        }
    }
}

void PezGlobo::drawTo(sf::RenderWindow& window) {
    window.draw(hitBox);
    for (auto& bala : balas) {
        bala->drawTo(window);
    }
}
