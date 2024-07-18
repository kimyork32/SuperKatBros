#include "ItemAji.h"

Aji::Aji(float x, float y) : Item(x, y) {
	this->velocidadX = 100.0f;
}


void Aji::disparar(Gato* gato, float x, float y, bool direccionizq) {
	gato->crearBala();
}