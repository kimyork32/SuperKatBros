#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Game.h"

class Menu {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    enum class MenuState {
        MainMenu,
        Game,
        Scores,
        Options
    };

    MenuState currentState;

    void loadResources();
    void setupMenu();
    void handleInput();
    void drawMenu();
    void drawMainMenu();
    void drawScores();
    void drawOptions();
    void drawText(const std::string& text, float x, float y, int size);

    std::unique_ptr<Game> game;

public:
    Menu(sf::RenderWindow& window);
    void run();
};

#endif // MENU_H
