#ifndef ERIZO_BUILDER_H
#define ERIZO_BUILDER_H

#include "EnemigoBuilder.h"
#include "Erizo.h"

class ErizoBuilder : public EnemigoBuilder {
public:
    ErizoBuilder() {
        enemigo = std::make_unique<Erizo>();
    }

    void buildPosicion(int x, int y) override {
        enemigo->setPosicion(x, y);
    }
    void buildAnchoHitbox() override {
        enemigo->setAnchoHitbox(50.f);
    }
    void buildAltoHitbox() override {
        enemigo->setAltoHitbox(60.f);
    }
    void buildTamanhoHitbox() override {
        enemigo->setTamanhoHitbox(enemigo->getAnchoHitbox(), enemigo->getAltoHitbox());
    }
    void buildExcesoSprite() override {
        enemigo->setExcesoSprite(0.f);
    }
    void buildAnchoSprite() override {
        enemigo->setAnchoSprite(25.f);
    }
    void buildAltoSprite() override {
        enemigo->setAltoSprite(39.f);
    }
    void buildEscalaX() override {
        enemigo->setEscalaX(enemigo->getAnchoHitbox() / enemigo->getAnchoSprite() + enemigo->getExcesoSprite());
    }
    void buildEscalaY() override {
        enemigo->setEscalaY(enemigo->getAltoHitbox() / enemigo->getAltoSprite() + enemigo->getExcesoSprite());
    }
    void buildVelocidadX() override {
        enemigo->setVelocidadX(320.f);
    }
    void buildVelocidadSprite() override {
        enemigo->setVelocidadSprite(100);
    }
    void buildGravedad() override {
        enemigo->setGravedad(4500.f);
    }
    void buildFuerzaSalto() override {
        enemigo->setFuerzaSalto(-8000.f);
    }
    void buildMasa() override {
        enemigo->setMasa(6.f);
    }
    void buildMaxTiempoSalto() override {
        enemigo->setMaxTiempoSalto(1.2f);
    }
    void buildSpritesFilename() override {
        enemigo->setSpriteMoverFilename("sprite.png");
    }
    void buildSprite() override {
        enemigo->loadSpriteSheet(enemigo->getSpriteMoverFilename());
    }
};

#endif // ERIZO_BUILDER_H
