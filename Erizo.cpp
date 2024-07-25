#include "Erizo.h"

Erizo::Erizo() : Enemigo(), speedBoostActive(false) {
    speedClock.restart();

}


void Erizo::aumentarVelocidad() {
    if (speedClock.getElapsedTime().asSeconds() >= speedBoostInterval) {
        velocidadX *= 2;
        speedBoostActive = true;
        speedClock.restart();
    }

    if (speedBoostActive && speedClock.getElapsedTime().asSeconds() >= speedBoostDuration) {
        velocidadX /= 2;
        speedBoostActive = false;
    }
}

void Erizo::update(float deltaTime, const std::vector<std::vector<int>>& map) {
    this->deltaTime = deltaTime;
    
    detectarPiso(map, this->PISO);
    detectarTecho(map);
    if (!verificarMoverseMismaPlataforma) {
        detectarObjDer(map);
        detectarObjIzq(map);
    }

    aumentarVelocidad(); 

    applyGravity();

    controlarMovimientoHorizontal(deltaTime);
    controlarMovimientoVertical();
    moverHorizontalSprite(left, right);
}

