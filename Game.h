#ifndef GAME_H
#define GAME_H

// Game.h
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <memory>
#include <thread>
#include <functional>

#include "BackGround.h"
#include "Gato.h"
#include "Colision.h"
#include "Mapa.h"
#include "Definitions.hpp"
#include "EnemigosManager.h"
#include "BloquesManager.h"
#include "ItemsManager.h"

class Game {
public:
    Game()
        : window(sf::VideoMode(windowSizeAncho, windowSizeAlto), "Mapa y Personaje"),
        colision(),
        view(sf::FloatRect(0, 0, windowSizeAncho, windowSizeAlto))
    {
        mapa = std::make_unique<Mapa>("map.txt", "tilemap_packed.png");
        gato = std::make_unique<Gato>(2 * cellSize, 2 * cellSize);

        enemigosManager = std::make_unique<EnemigosManager>();
        bloquesManager = std::make_unique<BloquesManager>();
        itemsManager = std::make_unique<ItemsManager>();

        enemigosManager->crearEnemigos(mapa);
        bloquesManager->crearBloques(mapa, gato);
        itemsManager->cargarPosicionesItemMap(mapa);
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

private:
    sf::RenderWindow window;
    sf::View view;
    Colision colision;
    std::unique_ptr<Mapa> mapa;
    std::unique_ptr<Gato> gato;
    std::unique_ptr<EnemigosManager> enemigosManager;
    std::unique_ptr<BloquesManager> bloquesManager;
    std::unique_ptr<ItemsManager> itemsManager;
    sf::Vector2f posWindowFloat;
    bool colisionLados = false;
    sf::Clock clock;

    void handleEvents();

    void determinarLimiteVentana();

    void update();

    void render();
};


#endif // !GAME_H
