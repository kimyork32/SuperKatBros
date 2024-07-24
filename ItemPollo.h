#pragma once
#ifndef ITEM_POLLO_H
#define ITEM_POLLO_H

#include "Item.h"

class Pollo : public Item {
private:
	int vidas;
public:
	Pollo(float, float);
	~Pollo() {}
	int getVidas();
};

#endif // ITEM_CATNIP_H