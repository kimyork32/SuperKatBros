#pragma once
#ifndef COLISION
#define COLISION

#include <vector>
#include <memory.h>
#include "Gato.h"
#include "Enemigo.h"
#include "Bloque.h"
#include "Mapa.h"
#include "Item.h"
#include "ItemMoneda.h"
#include "ItemCatnip.h"

class Colision {
private:
    //bool colisionLados = false;
	bool colisionArriba = false;
	bool colisionAbajo = false;
	bool colisionLadoIzq = false;
	bool colisionLadoDer = false;

public:
    Colision() {}
    void verificarColisionHitboxEnemigo(Gato* gato, std::vector<std::unique_ptr<Enemigo>>&);
	
	void verificarColisionHitboxItem(Gato* gato, std::vector<std::shared_ptr<Item>>&);
};

#endif // !COLISION

