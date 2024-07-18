#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <memory> 

#include "Gato.h"
#include "Enemigo.h"
#include "Serpiente.h"
#include "Rata.h"
#include "Erizo.h"
#include "Agila.h"
#include "PezGlobo.h"
#include "Colision.h"
#include "Mapa.h"
#include "Definitions.hpp"
#include "Bloque.h"
#include "BloqueDestruible.h"
#include "BloqueItem.h"
#include "BloqueMoneda.h"
#include "Item.h"
#include "ItemCatnip.h"
#include "ItemMoneda.h"

class Game {
public:
    Game()
        : window(sf::VideoMode(windowSize, windowSize), "Mapa y Personaje"),
        colision(),
        mapa("map.txt", "mapaSplit.png")
    {
        gato = std::make_unique<Gato>(11 * cellSize, 2 * cellSize);
        crearEnemigos();
        crearBloques();
        window.setView(view);
        serpiente = std::make_unique<Serpiente>(5, 10);
        erizo = std::make_unique<Erizo>(15, 20);
        pezGlobo = std::make_unique<PezGlobo>(25, 30);
        rata = std::make_unique<Rata>(35, 40);
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
    std::vector<std::shared_ptr<Bloque>> bloques;
    std::vector<std::shared_ptr<Item>> items;
   
    // objetos clonables enemigo
    std::unique_ptr<Enemigo> serpiente = std::make_unique<Serpiente>(-1, -1);
    std::unique_ptr<Enemigo> erizo = std::make_unique<Erizo>(-1, -1);
    std::unique_ptr<Enemigo> pezGlobo = std::make_unique<PezGlobo>(-1, -1);
    std::unique_ptr<Enemigo> rata = std::make_unique<Rata>(-1, -1);
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
            if (auto* pezGlobo = dynamic_cast<PezGlobo*>(enemigo.get())) {
                pezGlobo->verificarColisionBalaGato(gato);
            }

        }

        // update enemigos
        for (auto& item : items) {
            item->update(deltaTime, mapa.getMap());
        }

        //verificar colision gato-enemigos
        colision.verificarColisionHitboxEnemigo(gato.get(), enemigos);
        //veriEne();

        //verificar colision gato-bloques
        verificarColisionGatoBloque();

        //verificar colision gato-items
        colision.verificarColisionHitboxItem(gato.get(), items);

        //std::cout << "monedas: " << gato->getMonedas() << std::endl;
        
        
        //std::cout << "tam vect items: " << items.size() << std::endl;

        
        // Centrar la vista en el personaje
        view.setCenter(gato->getPosition().x + cellSize / 2, gato->getPosition().y + cellSize / 2);
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

        // Dibujar items
        for (auto& item : items) {
            item->drawTo(window);
        }


        window.display();
    }

    void crearEnemigos() {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (mapa.getValMap(i, j) == valEnemigoRata) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(std::make_unique<Rata>(j * cellSize, i * cellSize));
                    //enemigos.push_back(rata->clone(j * cellSize, i * cellSize));
                    enemigos.back()->moverseMismaPlataforma(mapa.getMap());
                    mapa.setValMap(i, j, 0);
                }
                else if (mapa.getValMap(i, j) == valEnemigoErizo) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(std::make_unique<Erizo>(j * cellSize, i * cellSize));
                    enemigos.back()->moverseMismaPlataforma(mapa.getMap());
                    mapa.setValMap(i, j, 0);
                }
                else if (mapa.getValMap(i, j) == valEnemigoSerpiente) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(std::make_unique<Serpiente>(j * cellSize, i * cellSize));
                    enemigos.back()->moverseMismaPlataforma(mapa.getMap());
                    mapa.setValMap(i, j, 0);
                }
                else if (mapa.getValMap(i, j) == valEnemigoPezGlobo) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(std::make_unique<PezGlobo>(j * cellSize, i * cellSize));
                    //enemigos.back()->moverseMismaPlataforma(mapa.getMap());
                    mapa.setValMap(i, j, 0);
                }
                else if (mapa.getValMap(i, j) == valEnemigoAgila) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(std::make_unique<Agila>(j * cellSize, i * cellSize));
                    //enemigos.back()->moverseMismaPlataforma(mapa.getMap());
                    mapa.setValMap(i, j, 0);
                }
            }
        }
    }

    void crearBloques() {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (mapa.getValMap(i, j) == valBloqueDestruible) {
                    bloques.push_back(std::make_shared<BloqueDestruible>(j * cellSize, i * cellSize));
                    gato->addObserver(bloques.back());
                }
                else if (mapa.getValMap(i, j) == valBloqueMoneda) {
                    bloques.push_back(std::make_shared<BloqueMoneda>(j * cellSize, i * cellSize, 3));
                    gato->addObserver(bloques.back());
                }
                else if (mapa.getValMap(i, j) == valBloqueItem) {
                    bloques.push_back(std::make_shared<BloqueItem>(j * cellSize, i * cellSize));
                    gato->addObserver(bloques.back());
                }
                else if (mapa.getValMap(i, j) == valBloqueItem) {
                    bloques.push_back(std::make_shared<BloqueItem>(j * cellSize, i * cellSize));
                    gato->addObserver(bloques.back());
                }
            }
        }
    }

    void verificarColisionGatoBloque() {
        for (size_t i = 0; i < bloques.size();) {
            if (bloques[i]->verificarColision()) {
                if (auto bloqueDestruible = std::dynamic_pointer_cast<BloqueDestruible>(bloques[i])) {
                    bloqueDestruible->setColisionDetect(false);
                    mapa.setValMap(static_cast<int>(bloques[i]->getPosY() / cellSize), static_cast<int>(bloques[i]->getPosX() / cellSize), 0);
                    gato->deleteObserver(bloqueDestruible);
                    bloques.erase(bloques.begin() + i);

                    continue; 
                }

                if (auto bloqueMoneda = std::dynamic_pointer_cast<BloqueMoneda>(bloques[i])) {
                        std::cout << "entrando veri" << std::endl;
                        std::unique_ptr<Item> item = std::make_unique<Moneda>(bloques[i]->getPosX(), bloques[i]->getPosY() - cellSize);
                        items.push_back(std::move(item));
                        bloqueMoneda->disminuirVida();
                        bloqueMoneda->setColisionDetect(false);
                    if (bloqueMoneda->getVidas() <= 0) {
                        gato->deleteObserver(bloqueMoneda);
                        continue; 
                    }
                   
                }


                if (auto bloqueItem = std::dynamic_pointer_cast<BloqueItem>(bloques[i])) {
                    sf::Vector2i valOJbSuperior;
                    valOJbSuperior.x = bloqueItem->getPosX() / cellSize;
                    valOJbSuperior.y = bloqueItem->getPosY() / cellSize;

                    //if (mapa.getValMap(valOJbSuperior.y - 1, valOJbSuperior.x) == valItemCatnip) {
                        std::unique_ptr<Item> item = std::make_unique<Catnip>(bloques[i]->getPosX(), bloques[i]->getPosY() - cellSize);
                        items.push_back(std::move(item));
                    //}
                    //else {
                    //    std::unique_ptr<Item> item = std::make_unique<Moneda>(bloques[i]->getPosX(), bloques[i]->getPosY() - cellSize);
                    //    items.push_back(std::move(item));
                    //}

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
