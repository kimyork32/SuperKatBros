#ifndef SCORES_MENU_HANDLER_H
#define SCORES_MENU_HANDLER_H

#include "MenuHandler.h"

class ScoreMenuH : public MenuHandler {
public:
    void handleInput(const sf::Event& event) override;
};

#endif // SCORES_MENU_HANDLER_H
