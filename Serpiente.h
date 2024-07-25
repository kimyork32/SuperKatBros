#ifndef SERPIENTE_H
#define SERPIENTE_H

#include "Enemigo.h"
#include <vector>
#include <memory>

class Serpiente : public Enemigo {
public:

    Serpiente();

    void update(float deltaTime, const std::vector<std::vector<int>>&) override;

private:
    void saltar();
   
};

#endif // SERPIENTE_H
