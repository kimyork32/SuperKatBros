#include "Erizo.h"

Erizo::Erizo(float x, float y) : Enemigo(x, y), speedBoostActive(false) {
    // Inicializa el reloj para el aumento de velocidad
    speedClock.restart();
    loadSpriteSheet("sprite.png");

}

Erizo::Erizo(Erizo& other) : Enemigo(other), speedClock(other.speedClock) {}


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

    aumentarVelocidad(); // Aumentar la velocidad según el tiempo

    applyGravity();

    controlarMovimientoHorizontal(deltaTime);
    controlarMovimientoVertical();
    moverHorizontalSprite(left, right);
}

std::unique_ptr<CloneableEnemigo> Erizo::clone(int newX, int newY) const {
    return std::make_unique<Erizo>(newX, newY);
}