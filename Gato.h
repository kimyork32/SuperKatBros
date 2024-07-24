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

    sf::Texture texturaGatoParado;
    sf::Sprite spriteGatoParado;
    
    sf::Texture texturaGatoCaminar;
    sf::Sprite spriteGatoCaminar;

    sf::Texture texturaGatoSaltando;
    sf::Sprite spriteGatoSaltando;

    int xTexture;
	 
    const float anchoSprite = 32.0f;   // 100.0f x 4    s a w d
    const float altoSprite = 32.0f;    // 195.0f x 5

    const float anchoSpriteParado = 32.0f;
    const float altoSpriteParado = 32.0f;

    const int numFigurasSprite = 8;

    const float anchoHitbox = 50.0f;
    const float altoHitbox = 60.0f;  

	const float excesoSprite = 1.0f;
    const float escalaX = anchoHitbox / anchoSpriteParado + excesoSprite;
    const float escalaY = altoHitbox / altoSpriteParado + excesoSprite;
    
    /*velocidadX;
    float velocidadY;*/
    float velocidadX = 370.0f;
    float velocidadY = 0.0f;
    float velocidadVariableX;
    float velocidadVariableY;

    float countSpriteCambio = 0.f;
    
    float velocidadSpriteParado = 30.f;

    const int velocidadSprite = 50; // a menor es el valor -> mas rapido es el sprite

    
    bool left;
    bool right;

    unsigned int monedas;

    bool stopDer = false;
    bool stopIzq = false;
    bool mirandoIzq = false;
    bool jumping = false;
    bool colisionPiso = false;

    
    bool spliteMiraLeft = false;
    bool spliteEscalado = false;

    float jumpTime;

    bool jumpButtonPressed;

    
    bool isAumentarVelocidadUsado = false;


    sf::Vector2f TECHO;
	sf::Vector2f PISO;
	sf::Vector2f OBJDER;
	sf::Vector2f OBJIZQ;
;
    bool spacePressed;
    float deltaTime;
    sf::Clock clock2;

    int yTexture = 0;


    std::vector<std::unique_ptr<Bala>> balas;


public:
    

    Gato(float, float);

    void processEvents(const sf::Event&);

    void saltar();

    //float Gato::calcularAltura();

    void detectarPisoTecho(const std::vector<std::vector<int>>&);

    void detectarObjIzqDer(const std::vector<std::vector<int>>&);

    void update(float, const std::vector<std::vector<int>>&);

    sf::Vector2f getPosition() const;

    void controlarSalto();

    void controlarMovimientoVertical(const std::vector<std::vector<int>>&);

    void controlarMovimientoHorizontal(float, const std::vector<std::vector<int>>&);

	void loadSpriteSheet();

    //void moverHorizontalSprite();
    
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

    float getVelocidadY();

    unsigned int getMonedas();

    void aumentarMonedas();

    void crearBala();

    void drawTo(sf::RenderWindow&);

    void drawSprites(sf::RenderWindow& window);

    void moverSprites();

};


#endif // !GATO