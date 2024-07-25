#pragma once

#ifndef RATA_H
#define RATA_H

#include <vector>
#include "Enemigo.h"

class Rata : public Enemigo {
public:
    Rata() : Enemigo() {}

    void update(float deltaTime, const std::vector<std::vector<int>>&) override;

};

#endif // RATA_H

