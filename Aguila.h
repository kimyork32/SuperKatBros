#pragma once
#ifndef AGUILA_H
#define AGUILA_H

#include "Enemigo.h"
#include <vector>
#include <cmath>

#define M_PI 3.14159265358979323846

class Aguila : public Enemigo {
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
    Aguila(float, float);

    Aguila(const Aguila& other);

    ~Aguila() {};

    void update(float deltaTime, const std::vector<std::vector<int>>&) override;

    void determinarExtremosX();

    void determinarVuelo();

    std::unique_ptr<CloneableEnemigo> clone(int newX, int newY) const override;
};

#endif // AGUILA_H