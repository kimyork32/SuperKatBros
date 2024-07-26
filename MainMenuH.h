#ifndef MAIN_MENU_HANDLER_H
#define MAIN_MENU_HANDLER_H

#include "MenuHandler.h"

class MainMenuH : public MenuHandler {
public:
    void handleInput(const sf::Event& event) override;
};

#endif // MAIN_MENU_HANDLER_H
