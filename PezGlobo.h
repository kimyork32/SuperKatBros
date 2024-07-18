#pragma once
#ifndef PEZ_GLOBO_H
#define PEZ_GLOBO_H

#include "Enemigo.h"
#include "Bala.h"
#include "Gato.h"
#include <vector>
#include <memory>

//class Gato;

class PezGlobo: public Enemigo {
private:
    std::vector<std::unique_ptr<Bala>> balas;
    bool vistaIzq = true;
    sf::Clock relojIntervaloBala;
    sf::Clock relojMovimientoDireccion;

public:
    PezGlobo(float, float);

    PezGlobo(const PezGlobo& other);

    ~PezGlobo();

    void update(float deltaTime, const std::vector<std::vector<int>>&) override;

    void disparar();

    void verificarColisionBalaGato(std::unique_ptr<Gato>&);

    void verificarColisionBalaBloque();
    
    void verificarTiempoVidaBalas();

    void drawTo(sf::RenderWindow& window) override;

    std::unique_ptr<CloneableEnemigo> clone(int newX, int newY) const override;

};

#endif // PEZ_GLOBO_H