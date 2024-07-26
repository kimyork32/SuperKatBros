#include "MainMenuH.h"
#include <iostream>

void MainMenuH::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonReleased) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition();
        sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);

        if (mousePosFloat.y >= 100 && mousePosFloat.y <= 150) {
            std::cout << "Inicio del juego" << std::endl;
            // Aquí deberías manejar el cambio al estado de juego
        }
        else if (mousePosFloat.y >= 200 && mousePosFloat.y <= 250) {
            std::cout << "Mostrar puntuaciones" << std::endl;
            // Aquí deberías manejar el cambio al estado de puntuaciones
        }
        else if (mousePosFloat.y >= 300 && mousePosFloat.y <= 350) {
            std::cout << "Mostrar opciones" << std::endl;
            // Aquí deberías manejar el cambio al estado de opciones
        }
        else if (mousePosFloat.y >= 400 && mousePosFloat.y <= 450) {
            std::cout << "Cerrar el juego" << std::endl;
            // Aquí deberías manejar el cierre del juego
        }
        else if (nextHandler) {
            nextHandler->handleInput(event);
        }
    }
    else if (nextHandler) {
        nextHandler->handleInput(event);
    }
}
