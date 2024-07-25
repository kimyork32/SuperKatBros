#include "Rata.h"


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

