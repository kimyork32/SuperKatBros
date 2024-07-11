#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <memory> 

#include "Gato.h"
#include "Enemigo.h"
#include "Serpiente.h"
#include "Erizo.h"
#include "Colision.h"
#include "Mapa.h"
#include "Definitions.hpp"
#include "Bloque.h"
#include "BloqueDestruible.h"
#include "BloqueItem.h"
#include "BloqueMoneda.h"
#include "Item.h"

class Game {
public:
    Game()
        : window(sf::VideoMode(windowSize, windowSize), "Mapa y Personaje"),
        colision(),
        mapa("map.txt", "mapaSplit.png")
    {
        gato = std::make_unique<Gato>(2 * cellSize, 2 * cellSize);
        crearEnemigos();
        crearBloques();
        window.setView(view);
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
    std::unique_ptr<Gato> gato;
    std::vector<std::unique_ptr<Enemigo>> enemigos;
    std::vector<std::unique_ptr<Bloque>> bloques;
   
    Mapa mapa;
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

    void update() {
        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asMilliseconds() < 16) {
            sf::sleep(sf::milliseconds(16 - elapsed.asMilliseconds()));
        }
        float deltaTime = clock.restart().asSeconds();
        
        // update gato
        gato->update(deltaTime, mapa.getMap());

        // update enemigos
        for (auto& enemigo : enemigos) {
            enemigo->update(deltaTime, mapa.getMap());
        }

        //verificar colision gato-enemigos
        colision.verificarColisionHitboxEnemigo(gato.get(), enemigos);
        //veriEne();

        //verificar colision gato-bloque
        verificarColisionGatoBloque();

        
        // Centrar la vista en el personaje
        view.setCenter(gato->getPosition().x + cellSize/2, gato->getPosition().y + cellSize/2);
        window.setView(view);
    }

    void render() {
        window.clear(sf::Color(0, 191, 255));

        // Dibujar mapa
        mapa.draw(window);

        // Dibujar el personaje
        gato->drawTo(window);

        // Dibujar enemigo
        for (auto& enemigo : enemigos) {
            enemigo->drawTo(window);
        }

        // Dibujar bloques
        for (auto& bloque : bloques) {
            bloque->drawTo(window);
        }

        window.display();
    }

    void crearEnemigos() {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (mapa.getValMap(i, j) == 57) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(std::make_unique<Enemigo>(j * cellSize, i * cellSize));
                    mapa.setValMap(i, j, 0);
                }
                else if (mapa.getValMap(i, j) == 58) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(std::make_unique<Erizo>(j * cellSize, i * cellSize));
                    mapa.setValMap(i, j, 0);
                }
                else if (mapa.getValMap(i, j) == 59) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(std::make_unique<Serpiente>(j * cellSize, i * cellSize));
                    mapa.setValMap(i, j, 0);
                }
            }
        }
    }

    void crearBloques() {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (mapa.getValMap(i, j) == 50) {
                    std::cout << "Bloque en " << i << " " << j << std::endl;
                    bloques.push_back(std::make_unique<BloqueDestruible>(j * cellSize, i * cellSize));
                    gato->addObserver(bloques.back().get());
                }
                else if (mapa.getValMap(i, j) == 51) {
                    std::cout << "Bloque en " << i << " " << j << std::endl;
                    bloques.push_back(std::make_unique<BloqueMoneda>(j * cellSize, i * cellSize));
                    gato->addObserver(bloques.back().get());
                }
                else if (mapa.getValMap(i, j) == 52) {
                    std::cout << "Bloque en " << i << " " << j << std::endl;
                    bloques.push_back(std::make_unique<BloqueItem>(j * cellSize, i * cellSize));
                    gato->addObserver(bloques.back().get());
                }
            }
        }
    }

    void verificarColisionGatoBloque() {
        for (size_t i = 0; i < bloques.size(); /* no incrementar i aquí */) {
            if (bloques[i]->verificarColision()) {
                mapa.setValMap(bloques[i]->getPosY() / cellSize, bloques[i]->getPosX() / cellSize, 0);
                bloques.erase(bloques.begin() + i);
                gato->deleteObserver(i);
            }
            ++i;
        }
        //std::cout << bloques.size() << std::endl;
    }
    
};
