#include "Serpiente.h"

Serpiente::Serpiente(float x, float y) : Enemigo(x, y) {
}

void Serpiente::saltar() {
    if (getPosY() + 1 >= PISO - getAltoHitbox()) {
        velocidadY = JUMP_FORCE / MASS;
        jumpTime = 0.0f;
    }
    jumpTime += deltaTime;
    velocidadY += (JUMP_FORCE / MASS) * deltaTime / MAX_JUMP_TIME;
}

void Serpiente::update(float deltaTime, const std::vector<std::vector<int>>& map) {
    this->deltaTime = deltaTime;

    detectarObjIzqDer(map);
    detectarPisoTecho(map);

    saltar();
    applyGravity();

    controlarMovimientoHorizontal(deltaTime, map);
    controlarMovimientoVertical(map);
    moverHorizontalSprite(left, right);
}
