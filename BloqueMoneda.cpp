#include "BloqueMoneda.h"

BloqueMoneda::BloqueMoneda(float x, float y, unsigned int vidas) : Bloque(x, y) {
	hitBox.setFillColor(sf::Color::Yellow);
	this->vidas = vidas;
	this->type = "BM";
	this->itemDropeado = false;

}

bool BloqueMoneda::verificarItemDropeado() {
	return itemDropeado;
}

void BloqueMoneda::setItemDropeado(bool itemDropeado) {
	this->itemDropeado = itemDropeado;
}