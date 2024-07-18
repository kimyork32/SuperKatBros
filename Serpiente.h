#ifndef SERPIENTE_H
#define SERPIENTE_H

#include "Enemigo.h"
#include <vector>
#include <memory>

class Serpiente : public Enemigo {
public:
    Serpiente(float x, float y);

    Serpiente(const Serpiente& other);

    void update(float deltaTime, const std::vector<std::vector<int>>&) override;

    std::unique_ptr<CloneableEnemigo> clone(int newX, int newY) const override;

private:
    void saltar();
   
};

#endif // SERPIENTE_H
