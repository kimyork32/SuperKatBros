#include "ItemCatnip.h"

Catnip::Catnip(float x, float y) : Item(x, y) {
	this->velocidadX = 200.0f;
}
float Catnip::getVelocidadX() {
	return velocidadX;
}

