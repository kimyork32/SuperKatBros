#ifndef ITEM_MONEDA_H
#define ITEM_MONEDA_H

#include "Item.h"

class Moneda : public Item {
public:
	Moneda(float, float);

	~Moneda() {}

	//void aumentarMonedas(Gato*&);

	void update(float deltaTime, const std::vector<std::vector<int>>& map) override;

};

#endif // ITEM_MONEDA_H