#include "Serpiente.h"

Serpiente::Serpiente(float x, float y) : Enemigo(x, y) {
}

Serpiente::Serpiente(const Serpiente& other) : Enemigo(other) {}

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
    //std::cout << deteccionPiso.y << " " << pisoUnicoPlataforma.y << std::endl;
}

std::unique_ptr<CloneableEnemigo> Serpiente::clone (int newX, int newY) const {
    return std::make_unique<Serpiente>(newX, newY);
}