#ifndef SERPIENTE_H
#define SERPIENTE_H

#include "Enemigo.h"

class Serpiente : public Enemigo {
public:
    Serpiente(float x, float y);
    void update(float deltaTime, const std::vector<std::vector<int>>& map) override;

private:
    void saltar();
};

#endif // SERPIENTE_H
