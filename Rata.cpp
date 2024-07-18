#include "Rata.h"

Rata::Rata(float x, float y) : Enemigo(x, y) {
    loadSpriteSheet("sprite.png");
}

Rata::Rata(const Rata& other) : Enemigo(other) {}


void Rata::update(float deltaTime, const std::vector<std::vector<int>>& map) {
    this->deltaTime = deltaTime;
    detectarPiso(map, this->PISO);
    detectarTecho(map);
    if (!verificarMoverseMismaPlataforma) {
        detectarObjDer(map);
        detectarObjIzq(map);
    }

    applyGravity();

    detectarPisoRoto(map);
    controlarMovimientoHorizontal(deltaTime);
    controlarMovimientoVertical();
    moverHorizontalSprite(left, right);
}

std::unique_ptr<CloneableEnemigo> Rata::clone(int newX, int newY) const {
    return std::make_unique<Rata>(newX, newY);
}