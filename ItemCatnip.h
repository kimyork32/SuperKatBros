#pragma once
#ifndef ITEM_CATNIP_H
#define ITEM_CATNIP_H

#include "Item.h"

class Catnip : public Item {
private:
	float velocidadX;
public:
	Catnip(float, float);
	~Catnip() {}
	//void aumentarVelocidad(Gato*&);
	float getVelocidadX();
};

#endif // ITEM_CATNIP_H