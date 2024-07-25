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

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            gato->processEvents(event);
        }
    }

    void determinarLimiteVentana() {
        posWindowFloat.x = gato->getPosX();
        posWindowFloat.y = gato->getPosY();

        if (windowSizeAlto > numRows * cellSize) {
            posWindowFloat.y = numRows * cellSize - windowSizeAlto / 2;
        }
        else if (posWindowFloat.y < windowSizeAlto / 2) {
            posWindowFloat.y = windowSizeAlto / 2;
        }
        else if (posWindowFloat.y > numRows * cellSize - windowSizeAlto / 2) {
            posWindowFloat.y = numRows * cellSize - windowSizeAlto / 2;
        }

        if (windowSizeAncho > numCols * cellSize) {
            posWindowFloat.x = windowSizeAncho / 2;
        }
        else if (posWindowFloat.x < windowSizeAncho / 2) {
            posWindowFloat.x = windowSizeAncho / 2;
        }
        else if (posWindowFloat.x > numCols * cellSize - windowSizeAncho / 2) {
            posWindowFloat.x = numCols * cellSize - windowSizeAncho / 2;
        }
    }

    void update() {
        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asMilliseconds() < 16) {
            sf::sleep(sf::milliseconds(16 - elapsed.asMilliseconds()));
        }
        float deltaTime = clock.restart().asSeconds();

        auto gatoUpdate = [this, deltaTime]() { gato->update(deltaTime, mapa->getMap()); };
        auto enemigosUpdate = [this, deltaTime]() { enemigosManager->update(deltaTime, mapa->getMap(), *gato); };
        auto itemsUpdate = [this, deltaTime]() { itemsManager->update(deltaTime, mapa->getMap()); };

        std::thread threadGato(gatoUpdate);
        std::thread threadEnemigosManager(enemigosUpdate);
        std::thread threadItemsManager(itemsUpdate);

        threadGato.join();
        threadEnemigosManager.join();
        threadItemsManager.join();

        colision.verificarColisionHitboxEnemigo(gato, enemigosManager->getVectorEnemigos());
        colision.verificarColisionBalaEnemigo(gato, enemigosManager->getVectorEnemigos());
        bloquesManager->verificarColisionGatoBloque(gato, mapa, itemsManager);
        itemsManager->verificarColisionHitboxItem(gato);

        determinarLimiteVentana();
        view.setCenter(posWindowFloat);
        window.setView(view);
    }

    void render() {
        window.clear(sf::Color(0, 191, 255));
        mapa->draw(window);
        gato->drawTo(window);
        enemigosManager->draw(window);
        bloquesManager->draw(window);
        itemsManager->draw(window);
        window.display();
    }
};
