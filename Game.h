#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "Gato.h"
#include "Enemigo.h"
#include "Pepino.h"
#include "Erizo.h"
#include "Colision.h"
#include "Mapa.h"
#include "Definitions.hpp"



class Game {
public:
    Game() : window(sf::VideoMode(windowSize, windowSize), "Mapa y Personaje"),
        //view(sf::FloatRect(0, 0, windowSize/3*2, windowSize/3*2)),
        colision(),
        mapa("map.txt", "mapaSplit.png")
    {
        player = new Gato(2 * cellSize, 2 * cellSize);
        //enemigo1 = new Enemigo(3 * cellSize, 2 * cellSize);
        crearEnemigos();
        
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
    Gato* player;
	std::vector<Enemigo*> enemigos;
    Mapa mapa;
    bool colisionLados = false;

    sf::Clock clock;


    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            player->processEvents(event);
            
        }
    }

    void update() {
        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asMilliseconds() < 16) {
            sf::sleep(sf::milliseconds(16 - elapsed.asMilliseconds()));
        }
        float deltaTime = clock.restart().asSeconds();

        // update gato
        player->update(deltaTime, mapa.getMap());

        // update enemigos
        for (int i = 0; i < enemigos.size(); i++) {
            enemigos[i]->update(deltaTime, mapa.getMap());
        }
        
        //verificar colision enemigos-gato
        colision.verificarColisionHitbox(player, enemigos);
        /*for (size_t i = 0; i < enemigos.size(); i++) {
            colision.verificarColisionHitbox(player, enemigos[i], i);
            if (!i % 2) {
                std::cout << std::endl;
            }
        }*/

        // Centrar la vista en el personaje
        view.setCenter(player->getPosition().x + cellSize, player->getPosition().y + cellSize);
        window.setView(view);
    }
        
    void render() {
        window.clear(sf::Color(0, 191, 255));

        // Dibujar mapa
        mapa.draw(window);

        // Dibujar el personaje
        player->drawTo(window);

        // Dibujar enemigo
        for (int i = 0; i < enemigos.size(); i++) {
            enemigos[i]->drawTo(window);
        }
		


        window.display();
    }

    void crearEnemigos() {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (mapa.getValMap(i, j) == 50) { 
					std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(new Pepino(j * cellSize, i * cellSize));
                    mapa.setValMap(i, j, 0); 
                }
                else if (mapa.getValMap(i, j) == 51) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(new Erizo(j * cellSize, i * cellSize));
                    mapa.setValMap(i, j, 0);
                }
                else if (mapa.getValMap(i, j) == 52) {
                    std::cout << "Enemigo en " << i << " " << j << std::endl;
                    enemigos.push_back(new Enemigo(j * cellSize, i * cellSize));
                    mapa.setValMap(i, j, 0);
                }
            }
        }
    }

    
};