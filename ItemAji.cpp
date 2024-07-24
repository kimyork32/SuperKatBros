#include "ItemAji.h"

Aji::Aji(float x, float y) : Item(x, y) {
	std::cout << "item aji" << std::endl;
	//this->velocidadX = 100.0f;
	this->numBalas = 5;
}

int Aji::getBalas() const {
	return numBalas;
}