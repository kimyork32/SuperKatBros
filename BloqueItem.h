#pragma once
#ifndef BLOQUE_ITEM_H
#define BLOQUE_ITEM_H

#include "Bloque.h"
#include <SFML\Graphics.hpp>

class BloqueItem : public Bloque {
private:
	bool itemDropeado;
public:
	BloqueItem(float, float);

	bool verificarItemDropeado();

	void setItemDropeado(bool);

};


#endif // !BLOQUE_ITEM_H

