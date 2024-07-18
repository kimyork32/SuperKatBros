#ifndef GATO_H
#define GATO_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include "Definitions.hpp"
#include "SubjectColision.h"
#include "Bala.h"



class Gato : public SubjectColision {
private:
    
    sf::RectangleShape hitBox;

    sf::Texture texturaGato;
    sf::Sprite spriteGato;

	 
    const float anchoSprite = 25.0f;   // 100.0f x 4    s a w d
    const float altoSprite = 39.0f;    // 195.0f x 5

    const float anchoHitbox = 50.0f;
    const float altoHitbox = 60.0f;  

	const float excesoSprite = 1.0f;
    const float escalaX = anchoHitbox / anchoSprite + excesoSprite;
    const float escalaY = altoHitbox / altoSprite + excesoSprite;
    
    /*velocidadX;
    float velocidadY;*/
    float velocidadX = 370.0f;
    float velocidadY = 0.0f;

    const int velocidadSprite = 120; // a menor es el valor -> mas rapido es el sprite

    bool jumping = false;
    
    bool left;
    bool right;

    unsigned int monedas;

    bool stopDer = false;
    bool stopIzq = false;


    float jumpTime;

    bool jumpButtonPressed;

    
    bool isAumentarVelocidadUsado = false;


    sf::Vector2f TECHO;
	sf::Vector2f PISO;
	sf::Vector2f OBJDER;
	sf::Vector2f OBJIZQ;

    bool teclaSuelta;
    bool spacePressed;
    float deltaTime;
    sf::Clock clock2;

    int yTexture = 0;


    std::vector<std::unique_ptr<Bala>> balas;


public:
    

    Gato(float, float);

    void processEvents(const sf::Event&);

    void saltar();
    
    void detectarPisoTecho(const std::vector<std::vector<int>>&);

    void detectarObjIzqDer(const std::vector<std::vector<int>>&);

    void update(float, const std::vector<std::vector<int>>&);

    void drawTo(sf::RenderWindow& );

    sf::Vector2f getPosition() const;

    void controlarSalto();

    void applyGravity();

    void controlarMovimientoVertical(const std::vector<std::vector<int>>&);

    void controlarMovimientoHorizontal(float, const std::vector<std::vector<int>>&);

	void loadSpriteSheet(const std::string&);

    void moverHorizontalSprite(bool, bool);
    
    sf::RectangleShape getHitBox();

    float getAnchoHitbox();

    float getAltoHitbox();

    float getPosX();

    float getPosY();

	//void setVelocidadX(float);

    void pararMovimientoXDer(float);
    
    void seguirMovimientoXDer();

        
    void morir();

    void collideWithBlock(int, int);

    void setVelocidadX(float);
    
    void aumentarVelocidadX(float);

    float getVelocidadX();

    unsigned int getMonedas();

    void aumentarMonedas();

    void crearBala();
};


#endif // !GATO