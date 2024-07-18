#pragma once
#ifndef ITEM_AJI_H
#define ITEM_AJI_H

#include "Item.h"
#include "gato.h"

class Aji : public Item {
private:
	
public:
	Aji(float, float);
	~Aji() {}
	void disparar(Gato*, float, float, bool);
};

#endif // ITEM_AJI_H