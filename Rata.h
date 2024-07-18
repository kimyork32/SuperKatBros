#pragma once

#ifndef RATA_H
#define RATA_H

#include <vector>
#include "Enemigo.h"

class Rata : public Enemigo {
public:
    Rata(float x, float y);

    Rata(const Rata& other);

    void update(float deltaTime, const std::vector<std::vector<int>>&) override;

    std::unique_ptr<CloneableEnemigo> clone(int newX, int newY) const override;
};

#endif // RATA_H

