#pragma once
#ifndef ITEMS_MANAGER_H
#define ITEMS_MANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Definitions.hpp"
#include "Mapa.h"
#include "Gato.h"
#include "Item.h"
#include "ItemCatnip.h"
#include "ItemMoneda.h"
#include "ItemAji.h"
#include "ItemPollo.h"
//#include "ItemPollo.h"

class ItemsManager {
private:
    std::vector<std::vector<int>> posicionesItemsMapa;
    std::vector<std::shared_ptr<Item>> items;


public:
    void cargarPosicionesItemMap(std::unique_ptr<Mapa>& mapa) {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (mapa->getValMap(i, j) == valItemAji) {
                    posicionesItemsMapa.push_back({ i, j, valItemAji });
                    mapa->setValMap(i, j, 0);
                }
                else if(mapa->getValMap(i, j) == valItemCatnip) {
                    posicionesItemsMapa.push_back({ i, j, valItemCatnip });
                    mapa->setValMap(i, j, 0);
                }
                else if (mapa->getValMap(i, j) == valItemMoneda) {
                    posicionesItemsMapa.push_back({ i, j, valItemMoneda });
                    mapa->setValMap(i, j, 0);
                }
                else if (mapa->getValMap(i, j) == valItemPollo) {
                    posicionesItemsMapa.push_back({ i, j, valItemPollo });
                    mapa->setValMap(i, j, 0);
                }
            }
        }
    }

    void verificarItemCreacion(int i, int j) {
        for (int k = 0; k < posicionesItemsMapa.size(); k++) {
            if (posicionesItemsMapa[k][0] == j - 1 && posicionesItemsMapa[k][1] == i) {
                if (posicionesItemsMapa[k][2] == valItemAji) {
                    
                    std::unique_ptr<Item> item = std::make_unique<Aji>(i * cellSize, (j - 1) * cellSize);
                    items.push_back(std::move(item));
                }
                else if (posicionesItemsMapa[k][2] == valItemCatnip) {
                    std::unique_ptr<Item> item = std::make_unique<Catnip>(i * cellSize, (j - 1) * cellSize);
                    items.push_back(std::move(item));
                }
                else if (posicionesItemsMapa[k][2] == valItemPollo) {
                    std::unique_ptr<Item> item = std::make_unique<Pollo>(i * cellSize, (j - 1) * cellSize);
                    items.push_back(std::move(item));
                }
            }
        }
    }
    
    void crearMoneda(int i, int j) {
        std::cout << "creando moneda" << std::endl;
        std::unique_ptr<Item> item = std::make_unique<Moneda>(i * cellSize, (j - 1) * cellSize);
        items.push_back(std::move(item));
    }


    void update(float deltaTime, const std::vector<std::vector<int>>& mapaMatriz) {
        for (auto& item : items) {
            item->update(deltaTime, mapaMatriz);
        }
    }

    std::vector<std::shared_ptr<Item>>& getVectorItems() {
        return items;
    }

    void draw(sf::RenderWindow& window) {
        for (auto& item : items) {
            item->drawTo(window);
        }
    }
    

    void verificarColisionHitboxItem(std::unique_ptr<Gato>& gato) {
        for (size_t i = 0; i < items.size(); i++) {
            if (items[i]->getHitBox().getGlobalBounds().intersects(gato->getHitBox().getGlobalBounds())) {
                if (auto moneda = std::dynamic_pointer_cast<Moneda>(items[i])) {
                    gato->aumentarMonedas();
                    items.erase(items.begin() + i);
                }
                else if (auto catnip = std::dynamic_pointer_cast<Catnip>(items[i])) {
                    gato->aumentarVelocidadX(catnip->getVelocidadX());
                    items.erase(items.begin() + i);
                }
                else if (auto pollo = std::dynamic_pointer_cast<Pollo>(items[i])) {
                    gato->setVidas(pollo->getVidas());
                    items.erase(items.begin() + i);
                }
                else if (auto aji = std::dynamic_pointer_cast<Aji>(items[i])) {
                    gato->setBalas(aji->getBalas());
                    items.erase(items.begin() + i);
                }
            }

            else {
                ++i;
            }
        }
    }



};
#endif // !ITEM_MANAGER_H

