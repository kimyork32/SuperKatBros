#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include "Gato.h"

#include <vector>
#include <cstdlib>
#include <ctime>


class Item {
protected:
    unsigned int count;
    sf::RectangleShape hitBox;

    sf::Texture texturaItem;
    sf::Sprite spriteItem;


    const float anchoSprite = 25.0f;   // 100.0f x 4    s a w d
    const float altoSprite = 39.0f;    // 195.0f x 5

    const float anchoHitbox = 40.0f;
    const float altoHitbox = 40.0f;

    const float excesoSprite = 0.0f;

    const float escalaX = anchoHitbox / anchoSprite + excesoSprite;
    const float escalaY = altoHitbox / altoSprite + excesoSprite;

    float velocidadX;
    float velocidadY;

    const int velocidadSprite = 100; // a menor es el valor -> mas rapido es el sprite

    bool jumping = false;
    bool rebote;
    bool stop = false;

    float TECHO;
    float PISO;

    float OBJDER;
    float OBJIZQ;

    float deltaTime;
    sf::Clock clock2;

    int yTexture = 0;

public:


    Item(float, float);

    ~Item();

    void detectarPisoTecho(const std::vector<std::vector<int>>&);

    void detectarObjIzqDer(const std::vector<std::vector<int>>&);

    void drawTo(sf::RenderWindow&);

    virtual void update(float, const std::vector<std::vector<int>>&);

    void applyGravity();

    void controlarMovimientoVertical(const std::vector<std::vector<int>>&);

    void controlarMovimientoHorizontal(float, const std::vector<std::vector<int>>&);

    sf::RectangleShape getHitBox();



};


#endif // !ITEM_H
