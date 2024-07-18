#pragma once
#ifndef AGILA_H
#define AGILA_H

#include "Enemigo.h"
#include <vector>
#include <cmath>

#define M_PI 3.14159265358979323846

class Agila : public Enemigo {
private:
    bool verificarMoverseMismaPlataforma = false;

    int maxRecorridoIzq;
    int maxRecorridoDer;

    float yCentro;
    float amplitud = 30; // Amplitud de la oscilación
    float frecuencia = 0.4; // Frecuencia en oscilaciones por segundo, asegurarse que no sea 0
    float fase = 0;
    sf::Clock relojOscilacion;

public:
    Agila(float, float);

    Agila(const Agila& other);

    ~Agila() {};

    void update(float deltaTime, const std::vector<std::vector<int>>&) override;

    void determinarExtremosX();

    void determinarVuelo();

    std::unique_ptr<CloneableEnemigo> clone(int newX, int newY) const override;
};

#endif // AGILA_H