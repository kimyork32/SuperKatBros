#pragma once
#ifndef COLISION
#define COLISION

#include <vector>
#include "Gato.h"
#include "Enemigo.h"

class Colision {
private:
    bool colisionLados = false;
    //bool colisionStatus = false;

public:
    Colision() {}
    void verificarColisionHitbox(Gato*, std::vector< Enemigo*>&);
};

#endif // !COLISION

