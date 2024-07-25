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
    float amplitud = 30; 
    float frecuencia = 0.4; 
    float fase = 0;
    sf::Clock relojOscilacion;

public:
    Aguila();


    ~Aguila() {};

    void update(float deltaTime, const std::vector<std::vector<int>>&) override;

    void determinarExtremosX();

    void determinarVuelo();

    void setYCentro(float);

    void setMaxRecorridoDer(float);

    void setMaxRecorridoIzq(float);
};

#endif // AGUILA_H