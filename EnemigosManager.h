#ifndef ENEMIGOS_MANAGER_H
#define ENEMIGOS_MANAGER_H

#include <vector>
#include <memory>

#include "Definitions.hpp"
#include "Mapa.h"
#include "Gato.h"
#include "Enemigo.h"
#include "PezGlobo.h"
#include "RataBuilder.h"
#include "ErizoBuilder.h"
#include "SerpienteBuilder.h"
#include "PezGloboBuilder.h"
#include "AguilaBuilder.h"
#include "EnemigosDirector.h"

class EnemigosManager {
private:
    std::vector<std::unique_ptr<Enemigo>> enemigos;
    RataBuilder enemigoRataBuilder;
    ErizoBuilder enemigoErizoBuilder;
    SerpienteBuilder enemigoSerpienteBuilder;
    PezGloboBuilder enemigoPezGloboBuilder;
    AguilaBuilder enemigoAguilaBuilder;
    EnemigosDirector director;

public:
    void crearEnemigos(std::unique_ptr<Mapa>& mapa) {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {

                if (mapa->getValMap(i, j) == valEnemigoRata) {
                    director.constructEnemigo(enemigoRataBuilder, j * cellSize, i * cellSize, cellSize, cellSize);
                    enemigos.push_back(enemigoRataBuilder.getEnemigo());
                    mapa->setValMap(i, j, 0);
                }
                else if (mapa->getValMap(i, j) == valEnemigoErizo) {
                    director.constructEnemigo(enemigoErizoBuilder, j * cellSize, i * cellSize, cellSize, cellSize);
                    enemigos.push_back(enemigoErizoBuilder.getEnemigo());
                    mapa->setValMap(i, j, 0);
                    enemigos.back()->moverseMismaPlataforma(mapa->getMap());
                }
                else if (mapa->getValMap(i, j) == valEnemigoSerpiente) {
                    director.constructEnemigo(enemigoSerpienteBuilder, j * cellSize, i * cellSize, cellSize, cellSize);
                    enemigos.push_back(enemigoSerpienteBuilder.getEnemigo());
                    mapa->setValMap(i, j, 0);
                    enemigos.back()->moverseMismaPlataforma(mapa->getMap());
                }
                else if (mapa->getValMap(i, j) == valEnemigoPezGlobo) {
                    director.constructEnemigo(enemigoPezGloboBuilder, j * cellSize, i * cellSize, cellSize, cellSize);
                    enemigos.push_back(enemigoPezGloboBuilder.getEnemigo());
                    mapa->setValMap(i, j, 0);
                }
                else if (mapa->getValMap(i, j) == valEnemigoAguila) {
                    director.constructEnemigo(enemigoAguilaBuilder, j * cellSize, i * cellSize, cellSize, cellSize);
                    std::unique_ptr<Enemigo> enemigoPtr = enemigoAguilaBuilder.getEnemigo();

                    if (auto* aguila = dynamic_cast<Aguila*>(enemigoPtr.get())) {
                        aguila->setYCentro(aguila->getPosY() + aguila->getAltoHitbox() / 2);
                        aguila->setMaxRecorridoDer(aguila->getPosX() + (6 * cellSize));
                        aguila->setMaxRecorridoIzq(aguila->getPosX() - ((6 + 1) * cellSize));
                    }

                    enemigos.push_back(std::move(enemigoPtr)); 
                    mapa->setValMap(i, j, 0);
                }
            }
        }
    }

    void update(float deltaTime, const std::vector<std::vector<int>>& mapaMatriz, Gato& gato) {
        for (auto& enemigo : enemigos) {
            enemigo->update(deltaTime, mapaMatriz);
            if (auto* pezGlobo = dynamic_cast<PezGlobo*>(enemigo.get())) {
                pezGlobo->verificarColisionBalaGato(gato);
            }
        }
    }

    std::vector<std::unique_ptr<Enemigo>>& getVectorEnemigos() {
        return enemigos;
    }

    void draw(sf::RenderWindow& window) {
        for (auto& enemigo : enemigos) {
            enemigo->drawTo(window);
        }
    }
};

#endif // ENEMIGOS_MANAGER_H
