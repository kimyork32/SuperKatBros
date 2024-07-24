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
#include "Bala.h"

class Colision {
private:
    //bool colisionLados = false;
	bool colisionArriba = false;
	bool colisionAbajo = false;
	bool colisionLadoIzq = false;
	bool colisionLadoDer = false;

public:
    Colision() {}
    void verificarColisionHitboxEnemigo(std::unique_ptr<Gato>& gato, std::vector<std::unique_ptr<Enemigo>>&);
	
	void verificarColisionHitboxItem(std::unique_ptr<Gato>& gato, std::vector<std::shared_ptr<Item>>&);

	void verificarColisionBalaEnemigo(std::unique_ptr<Gato>&, std::vector<std::unique_ptr<Enemigo>>&);
};

#endif // !COLISION

