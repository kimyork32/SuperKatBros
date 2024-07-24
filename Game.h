#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <memory> 

#include "BackGround.h"
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
        : window(sf::VideoMode(windowSizeAncho, windowSizeAlto), "Mapa y Personaje"),
        colision(),
        //background(),
        view(sf::FloatRect(0, 0, windowSizeAncho, windowSizeAlto)),
        mapa("map.txt", "mapaSplit.png")
    {
        gato = std::make_unique<Gato>(2 * cellSize, 2 * cellSize);
        crearEnemigos();
        crearBloques();
        //window.setView(view);
        background = std::make_unique< BackGround>();
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
    std::unique_ptr<BackGround> background;
    std::unique_ptr<Gato> gato;
    std::vector<std::unique_ptr<Enemigo>> enemigos;
    std::vector<std::shared_ptr<Bloque>> bloques;
    std::vector<std::shared_ptr<Item>> items;

    // Coordenadas ventana flotante
    sf::Vector2f posWindowFloat;
   
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

        // update fondo
        //background->update(posWindowFloat.x, posWindowFloat.y);
        //std::cout << posWindowFloat.x << " " << posWindowFloat.y << std::endl;
        background->update(posWindowFloat.x, posWindowFloat.y);

        //verificar colision gato-enemigos
        colision.verificarColisionHitboxEnemigo(gato.get(), enemigos);
        //veriEne();

        //verificar colision gato-bloques
        verificarColisionGatoBloque();

        //verificar colision gato-items
        colision.verificarColisionHitboxItem(gato.get(), items);

        //std::cout << "monedas: " << gato->getMonedas() << std::endl;
        
        
        //std::cout << "tam vect items: " << items.size() << std::endl;
        
        // Determinar coordenadas de la ventana
        determinarLimiteVentana();
        
        // Centrar la vista en el personaje
        //view.setCenter(posWindowFloat.x, posWindowFloat.y);

        //std::cout << numRows * cellSize << std::endl;
        view.setCenter(posWindowFloat);

        window.setView(view);
    }

    void render() {
        window.clear(sf::Color(0, 191, 255));
        
        // Dibujar fondo
        background->drawTo(window);

        // Dibujar mapa
        mapa.draw(window);

         //Dibujar el personaje
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

        // ########## TEST ##########
        //sf::RectangleShape test;
        //test.setFillColor(sf::Color::Yellow);
        ////test.setSize(windowSizeAncho, windowSizeAlto);
        //test.setPosition(0, 0);
        //window.draw(test);
        // ##########################

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
