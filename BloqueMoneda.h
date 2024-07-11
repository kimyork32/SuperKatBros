#pragma once
#ifndef BLOQUE_MONEDA_H
#define BLOQUE_MONEDA_H

#include "Bloque.h"
#include <SFML\Graphics.hpp>

class BloqueMoneda : public Bloque {
public:
	BloqueMoneda(float, float);
};


#endif // !BLOQUE_MONEDA_H