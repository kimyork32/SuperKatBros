#include "Game.h"


void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        gato->processEvents(event);
    }
}

void Game::determinarLimiteVentana() {
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

void Game::update() {
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

void Game::render() {
    window.clear(sf::Color(0, 191, 255));
    mapa->draw(window);
    gato->drawTo(window);
    enemigosManager->draw(window);
    bloquesManager->draw(window);
    itemsManager->draw(window);
    window.display();
}