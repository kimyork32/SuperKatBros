#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"
#include "CloneableEnemigo.h"

#include <iostream>
#include <vector>

class Enemigo : public CloneableEnemigo {
protected:

    sf::RectangleShape hitBox;

    sf::Texture texturaGato;
    sf::Sprite spriteGato;


    const float anchoSprite = 25.0f;
    const float altoSprite = 39.0f; 

    const float anchoHitbox = 50.0f;
    const float altoHitbox = 60.0f;

    const float excesoSprite = 0.0f;
    const float escalaX = anchoHitbox / anchoSprite + excesoSprite;
    const float escalaY = altoHitbox / altoSprite + excesoSprite;

    float velocidadX;
    float velocidadY;

    const int velocidadSprite = 100; // a menor es el valor -> mas rapido es el sprite

    bool jumping = false;

    bool left;
    bool right;
    bool rebote = false;
    bool stop = false;

    float jumpTime;

    bool jumpButtonPressed;


    // -1.0f solo para inicializar
    sf::Vector2f TECHO;
    sf::Vector2f PISO;

    float OBJDER = -1.0f;
    float OBJIZQ = -1.0f;

    bool teclaSuelta;
    bool spacePressed;
    float deltaTime;

    bool verificarMoverseMismaPlataforma = false;

    sf::Vector2f pisoUnicoPlataforma;
    sf::Vector2f deteccionPiso;

    int yTexture = 0;
    
    sf::Clock clock2;


public:


    Enemigo(float, float);

    //Enemigo(const Enemigo& other);

    virtual ~Enemigo() = default;

    bool colisionLados = false;


    virtual void detectarPiso(const std::vector<std::vector<int>>&, sf::Vector2f&);

    virtual void detectarTecho(const std::vector<std::vector<int>>&);

    virtual void detectarObjDer(const std::vector<std::vector<int>>&);

    virtual void detectarObjIzq(const std::vector<std::vector<int>>&);

    virtual void update(float, const std::vector<std::vector<int>>&) = 0;

    virtual void drawTo(sf::RenderWindow&);

    sf::Vector2f getPosition() const;


    void applyGravity();

    void controlarMovimientoVertical();

    virtual void controlarMovimientoHorizontal(float);

    void loadSpriteSheet(const std::string&);

    void moverHorizontalSprite(bool, bool);
    
	sf::RectangleShape getHitBox();

    float getAnchoHitbox();

    float getAltoHitbox();

    float getPosX();

    float getPosY();

    void parar();

    void detectarOjbIzqDerPlataforma(const std::vector<std::vector<int>> map, int);

    void moverseMismaPlataforma(const std::vector<std::vector<int>>);

    void detectarPisoRoto(const std::vector<std::vector<int>>);

};


#endif // !ENEMIGO