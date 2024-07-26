#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : window(window), currentState(MenuState::MainMenu) {
    loadResources();
    setupMenu();
}

void Menu::loadResources() {
    std::string fontPath = "SIXTY.ttf";
    std::string backgroundImagePath = "fondo.png";

    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Error al cargar la fuente desde: " + fontPath);
    }

    if (!backgroundTexture.loadFromFile(backgroundImagePath)) {
        throw std::runtime_error("Error al cargar la imagen de fondo desde: " + backgroundImagePath);
    }

    backgroundSprite.setTexture(backgroundTexture);
}

void Menu::setupMenu() {
    // Configura el menú si es necesario
}

void Menu::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePosition);
            if (currentState == MenuState::MainMenu) {
                if (mousePosFloat.y >= 100 && mousePosFloat.y <= 150) {
                    currentState = MenuState::Game;
                    game = std::make_unique<Game>();
                    game->run();
                }
                else if (mousePosFloat.y >= 200 && mousePosFloat.y <= 250) {
                    currentState = MenuState::Scores;
                }
                else if (mousePosFloat.y >= 300 && mousePosFloat.y <= 350) {
                    currentState = MenuState::Options;
                }
                else if (mousePosFloat.y >= 400 && mousePosFloat.y <= 450) {
                    window.close();
                }
            }
            else {
                currentState = MenuState::MainMenu;
            }
        }
    }
}

void Menu::drawMenu() {
    window.clear();
    window.draw(backgroundSprite);

    switch (currentState) {
    case MenuState::MainMenu:
        drawMainMenu();
        break;
    case MenuState::Game:
        break;
    case MenuState::Scores:
        drawScores();
        break;
    case MenuState::Options:
        drawOptions();
        break;
    }

    window.display();
}

void Menu::drawMainMenu() {
    drawText("Jugar", 100, 100, 32);
    drawText("Puntuaciones", 100, 200, 32);
    drawText("Opciones", 100, 300, 32);
    drawText("Salir", 100, 400, 32);
}

void Menu::drawScores() {
    window.clear(sf::Color::Black);
    drawText("Puntuaciones", 200, 50, 48);
    drawText("Jugador 1: 1000", 200, 150, 32);
    drawText("Jugador 2: 800", 200, 200, 32);
}

void Menu::drawOptions() {
    window.clear(sf::Color::Black);
    drawText("Opciones", 200, 50, 48);
    drawText("Volumen: 50%", 200, 150, 32);
}

void Menu::drawText(const std::string& text, float x, float y, int size) {
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(size);
    sfText.setPosition(x, y);
    sfText.setFillColor(sf::Color::White);
    window.draw(sfText);
}

void Menu::run() {
    while (window.isOpen()) {
        handleInput();
        if (currentState != MenuState::Game) {
            drawMenu();
        }
    }
}
