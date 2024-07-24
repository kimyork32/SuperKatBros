#include "ItemPollo.h"

Pollo::Pollo(float x, float y) : Item(x, y) {
	std::cout << "item pollo" << std::endl;
	//this-> velocidadX = 100.f;
	this->vidas = 1;
}
int Pollo::getVidas() {
	return vidas;
}

