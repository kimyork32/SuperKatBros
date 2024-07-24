#pragma once
#ifndef ITEM_AJI_H
#define ITEM_AJI_H

#include "Item.h"
#include "gato.h"

class Aji : public Item {
private:
	int numBalas;
	
public:
	Aji(float, float);
	~Aji() {}
	int getBalas() const;
};

#endif // ITEM_AJI_H