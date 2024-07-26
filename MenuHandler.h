#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include <SFML/Graphics.hpp>
#include <memory>

class MenuHandler {
protected:
    std::unique_ptr<MenuHandler> nextHandler;

public:
    virtual ~MenuHandler() = default;

    void setNextHandler(std::unique_ptr<MenuHandler> next) {
        nextHandler = std::move(next);
    }

    virtual void handleInput(const sf::Event& event) = 0;
};

#endif // MENU_HANDLER_H
