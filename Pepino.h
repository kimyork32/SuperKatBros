#ifndef PEPINO_H
#define PEPINO_H

#include "Enemigo.h"

class Pepino : public Enemigo {
public:
    Pepino(float x, float y);
    void update(float deltaTime, const std::vector<std::vector<int>>& map) override;

private:
    void saltar();
};

#endif // PEPINO_H
