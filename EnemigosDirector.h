#ifndef ENEMIGOS_DIRECTOR_H
#define ENEMIGOS_DIRECTOR_H

#include "EnemigoBuilder.h"


class EnemigosDirector {
public:
    void constructEnemigo(EnemigoBuilder& builder, int x, int y, float ancho, float alto) {
        builder.buildPosicion(x, y);
        builder.buildAnchoHitbox();
        builder.buildAltoHitbox();
        builder.buildTamanhoHitbox();
        builder.buildExcesoSprite();
        builder.buildAnchoSprite();
        builder.buildAltoSprite();
        builder.buildEscalaX();
        builder.buildEscalaY();
        builder.buildVelocidadX();
        builder.buildVelocidadSprite();
        builder.buildGravedad();
        builder.buildFuerzaSalto();
        builder.buildMasa();
        builder.buildMaxTiempoSalto();
        builder.buildSpritesFilename();
        builder.buildSprite();
    }

};

#endif // ENEMIGOS_DIRECTOR_H
