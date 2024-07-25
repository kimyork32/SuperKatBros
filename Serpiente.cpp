#include "Serpiente.h"


Serpiente::Serpiente() : Enemigo() {}


void Serpiente::saltar() {
    if (getPosY() + 1 >= PISO.y - getAltoHitbox()) {
        velocidadY = JUMP_FORCE / MASS;
        jumpTime = 0.0f;
    }
    jumpTime += deltaTime;
    velocidadY += (JUMP_FORCE / MASS) * deltaTime / MAX_JUMP_TIME;
}

void Serpiente::update(float deltaTime, const std::vector<std::vector<int>>& map) {
    this->deltaTime = deltaTime;

    detectarPiso(map, this->PISO);
    detectarTecho(map);
    if (!verificarMoverseMismaPlataforma) {
        detectarObjDer(map);
        detectarObjIzq(map);
    }

    saltar();
    applyGravity();

    controlarMovimientoHorizontal(deltaTime);
    controlarMovimientoVertical();
    moverHorizontalSprite(left, right);
    detectarPisoRoto(map);
}