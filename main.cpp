#include <SFML/Graphics.hpp>
#include "Menu.h"

int main() {
    
    std::cout << valEnemigoRata<< std::endl;
    std::cout << valEnemigoErizo << std::endl;
    std::cout << valEnemigoSerpiente << std::endl;
    std::cout << valEnemigoPezGlobo << std::endl;
    std::cout << valEnemigoAguila << std::endl;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SuperKat");

    Menu menu(window);
    menu.run();
    return 0;
}