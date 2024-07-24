#pragma once

#ifndef BLOQUES_MANAGER_H
#define BLOQUES_MANAGER_H

#include <vector>
#include <memory>

#include "Bloque.h"
#include "Mapa.h"
#include "Bloque.h"
#include "BloqueDestruible.h"
#include "BloqueItem.h"
#include "BloqueMoneda.h"
#include "Gato.h"
#include "Item.h"
#include "ItemCatnip.h"
#include "ItemMoneda.h"
#include "ItemsManager.h"



class BloquesManager {
private:
    std::vector<std::shared_ptr<Bloque>> bloques;
public:
    void update(sf::RenderWindow& window) {
        for (auto& bloque : bloques) {
            bloque->drawTo(window);
        }
    }

    void crearBloques(std::unique_ptr<Mapa>& mapa, std::unique_ptr<Gato>& gato) {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (mapa->getValMap(i, j) == valBloqueDestruible) {
                    bloques.push_back(std::make_shared<BloqueDestruible>(j * cellSize, i * cellSize));
                    gato->addObserver(bloques.back());
                }
                else if (mapa->getValMap(i, j) == valBloqueMoneda) {
                    bloques.push_back(std::make_shared<BloqueMoneda>(j * cellSize, i * cellSize, 3));
                    gato->addObserver(bloques.back());
                }
                else if (mapa->getValMap(i, j) == valBloqueItem) {
                    bloques.push_back(std::make_shared<BloqueItem>(j * cellSize, i * cellSize));
                    gato->addObserver(bloques.back());
                }
                else if (mapa->getValMap(i, j) == valBloqueItem) {
                    bloques.push_back(std::make_shared<BloqueItem>(j * cellSize, i * cellSize));
                    gato->addObserver(bloques.back());
                }
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (auto& bloque : bloques) {
            bloque->drawTo(window);
        }
    }

    std::vector<std::shared_ptr<Bloque>>& getVectorEnemigos() {
        return bloques;
    }

    void verificarColisionGatoBloque(std::unique_ptr<Gato>& gato, std::unique_ptr<Mapa>& mapa, std::unique_ptr<ItemsManager>& itemsManager) {
        for (size_t i = 0; i < bloques.size();) {
            if (bloques[i]->verificarColision()) {
                if (auto bloqueDestruible = std::dynamic_pointer_cast<BloqueDestruible>(bloques[i])) {
                    bloqueDestruible->setColisionDetect(false);
                    mapa->setValMap(static_cast<int>(bloques[i]->getPosY() / cellSize), static_cast<int>(bloques[i]->getPosX() / cellSize), 0);
                    gato->deleteObserver(bloqueDestruible);
                    bloques.erase(bloques.begin() + i);

                    continue;
                }

                if (auto bloqueMoneda = std::dynamic_pointer_cast<BloqueMoneda>(bloques[i])) {
                    itemsManager->crearMoneda(bloques[i]->getPosX() / cellSize, bloques[i]->getPosY() / cellSize);

                    bloqueMoneda->disminuirVida();
                    bloqueMoneda->setColisionDetect(false);
                    if (bloqueMoneda->getVidas() <= 0) {
                        gato->deleteObserver(bloqueMoneda);
                        continue;
                    }

                }


                if (auto bloqueItem = std::dynamic_pointer_cast<BloqueItem>(bloques[i])) {
                    itemsManager->verificarItemCreacion(bloques[i]->getPosX()/cellSize, bloques[i]->getPosY() / cellSize);

                    bloqueItem->disminuirVida();
                    bloqueItem->setColisionDetect(false);
                    if (bloqueItem->getVidas() <= 0) {
                        gato->deleteObserver(bloques[i]);
                        continue;
                    }
                }

            }

            ++i;
        }
    }
};



#endif // !BLOQUES_MANAGER_H
