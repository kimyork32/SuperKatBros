#include "BloqueItem.h"

BloqueItem::BloqueItem(float x, float y) : Bloque(x, y) {
	hitBox.setFillColor(sf::Color::Green);
	itemDropeado = false;
	this->vidas = 1;
	this->type = "BI";
}

bool BloqueItem::verificarItemDropeado() {
	return itemDropeado;
}

void BloqueItem::setItemDropeado(bool itemDropeado) {
	this->itemDropeado = itemDropeado;
}