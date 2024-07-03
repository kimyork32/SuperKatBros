#pragma once

#ifndef ERIZO_H
#define ERIZO_H

#include "Enemigo.h"

class Erizo : public Enemigo {
public:
    Erizo(float x, float y);
    void update(float deltaTime, const std::vector<std::vector<int>>& map) override;

private:
    void aumentarVelocidad();
    sf::Clock speedClock;
    bool speedBoostActive;
    const float speedBoostDuration = 1.0f;
    const float speedBoostInterval = 3.0f;
};

#endif // ERIZO_H
