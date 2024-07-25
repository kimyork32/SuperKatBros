#ifndef ENEMIGO_BUILDER_H
#define ENEMIGO_BUILDER_H

#include <memory>
#include "Enemigo.h"

class EnemigoBuilder {
protected:
    std::unique_ptr<Enemigo> enemigo;
public:
    virtual ~EnemigoBuilder() = default;
    virtual void buildPosicion(int, int) = 0;
    virtual void buildAnchoHitbox() = 0;
    virtual void buildAltoHitbox() = 0;
    virtual void buildTamanhoHitbox() = 0;
    virtual void buildExcesoSprite() = 0;
    virtual void buildAnchoSprite() = 0;
    virtual void buildAltoSprite() = 0;
    virtual void buildEscalaX() = 0;
    virtual void buildEscalaY() = 0;
    virtual void buildVelocidadX() = 0;
    virtual void buildVelocidadSprite() = 0;
    virtual void buildGravedad() = 0;
    virtual void buildFuerzaSalto() = 0;
    virtual void buildMasa() = 0;
    virtual void buildMaxTiempoSalto() = 0;
    virtual void buildSpritesFilename() = 0;
    virtual void buildSprite() = 0;

    std::unique_ptr<Enemigo> getEnemigo() {
        return std::move(enemigo);
    }
};

#endif // ENEMIGO_BUILDER_H
