#pragma once
#ifndef BLOQUE_MONEDA_H
#define BLOQUE_MONEDA_H

#include "Bloque.h"
#include <SFML\Graphics.hpp>

class BloqueMoneda : public Bloque {
//private:
	//unsigned int vidas;
	bool itemDropeado;

public:
	BloqueMoneda(float, float, unsigned int);

	bool verificarItemDropeado();

	void setItemDropeado(bool);
	//void disminuirVida();

	//unsigned int getVidas();
};


#endif // !BLOQUE_MONEDA_H