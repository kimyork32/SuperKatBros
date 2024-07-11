#include "Erizo.h"

Erizo::Erizo(float x, float y) : Enemigo(x, y), speedBoostActive(false) {
    // Inicializa el reloj para el aumento de velocidad
    speedClock.restart();
    loadSpriteSheet("sprite.png");

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

    detectarObjIzqDer(map);
    detectarPisoTecho(map);

    aumentarVelocidad(); // Aumentar la velocidad según el tiempo

    applyGravity();

    controlarMovimientoHorizontal(deltaTime, map);
    controlarMovimientoVertical(map);
    moverHorizontalSprite(left, right);
}
