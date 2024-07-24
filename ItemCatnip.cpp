#include "ItemCatnip.h"

Catnip::Catnip(float x, float y) : Item(x, y) {
	std::cout << "item catnip" << std::endl;
	this->velocidadX = 200.0f;
}
float Catnip::getVelocidadX() {
	return velocidadX;
}

