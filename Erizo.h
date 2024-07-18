#pragma once

#ifndef ERIZO_H
#define ERIZO_H

#include "Enemigo.h"
#include <vector>
#include <memory>

class Erizo : public Enemigo {
public:
    Erizo(float x, float y);

    Erizo(Erizo& other);
    
    void update(float deltaTime, const std::vector<std::vector<int>>&) override;

    std::unique_ptr<CloneableEnemigo> clone(int newX, int newY) const override;

private:
    void aumentarVelocidad();
    sf::Clock speedClock;
    bool speedBoostActive;
    const float speedBoostDuration = 1.0f;
    const float speedBoostInterval = 3.0f;
};

#endif // ERIZO_H

