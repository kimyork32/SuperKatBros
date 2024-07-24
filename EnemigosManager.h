#pragma once
#ifndef ENEMIGO_MANAGER_h
#define ENEMIGO_MANAGER_h

#include <vector>
#include <memory>

#include "Definitions.hpp"
#include "Mapa.h"
#include "Gato.h"
#include "Enemigo.h"
#include "Serpiente.h"
#include "Rata.h"
#include "Erizo.h"
#include "Aguila.h"
#include "PezGlobo.h"


class EnemigosManager {
private:
    std::vector<std::unique_ptr<Enemigo>> enemigos;

public:
    void crearEnemigos(std::unique_ptr<Mapa>& mapa) {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {

                if (mapa->getValMap(i, j) == valEnemigoRata) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(std::make_unique<Rata>(j * cellSize, i * cellSize));
                    //enemigos.push_back(rata->clone(j * cellSize, i * cellSize));
                    enemigos.back()->moverseMismaPlataforma(mapa->getMap());
                    mapa->setValMap(i, j, 0);
                }
                else if (mapa->getValMap(i, j) == valEnemigoErizo) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(std::make_unique<Erizo>(j * cellSize, i * cellSize));
                    enemigos.back()->moverseMismaPlataforma(mapa->getMap());
                    mapa->setValMap(i, j, 0);
                }
                else if (mapa->getValMap(i, j) == valEnemigoSerpiente) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(std::make_unique<Serpiente>(j * cellSize, i * cellSize));
                    enemigos.back()->moverseMismaPlataforma(mapa->getMap());
                    mapa->setValMap(i, j, 0);
                }
                else if (mapa->getValMap(i, j) == valEnemigoPezGlobo) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(std::make_unique<PezGlobo>(j * cellSize, i * cellSize));
                    //enemigos.back()->moverseMismaPlataforma(mapa.getMap());
                    mapa->setValMap(i, j, 0);
                }
                else if (mapa->getValMap(i, j) == valEnemigoAguila) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(std::make_unique<Aguila>(j * cellSize, i * cellSize));
                    //enemigos.back()->moverseMismaPlataforma(mapa.getMap());
                    mapa->setValMap(i, j, 0);
                }
            }
        }
    }
    
    void update(float deltaTime, const std::vector<std::vector<int>>& mapaMatriz, std::unique_ptr<Gato>& gato) {
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

#endif // !ENEMIGO_MANAGER_h
