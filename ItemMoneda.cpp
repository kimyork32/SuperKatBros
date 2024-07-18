#include "ItemMoneda.h"

Moneda::Moneda(float x, float y) : Item(x, y) {}

void Moneda::aumentarMonedas(Gato*& gato) {
	gato->aumentarMonedas();
}

void Moneda::update(float deltaTime, const std::vector<std::vector<int>>& map) {
    this->deltaTime = deltaTime;

    detectarObjIzqDer(map);
    detectarPisoTecho(map);

    applyGravity();

    //controlarMovimientoHorizontal(deltaTime, map);

    controlarMovimientoVertical(map);

    //moverHorizontalSprite(left, right);
}