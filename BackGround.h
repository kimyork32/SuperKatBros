#ifndef BACK_GROUND_h
#define BACK_GROUND_h

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Definitions.hpp"


class BackGround {
private:
	float velocidadX;
	float velocidadY;

	float posX;
	float posY;

	const float anchoSpriteBackground = 48.0f;
	const float altoSpriteBackground = 72.0f;

	//float anchoVistaSpriteBackground = 48.0f;
	//float altovistaSpriteBackground = 20.0f;

	const float excesoSprite = 0.0f;
	const float escalaX = windowSizeAncho / anchoSpriteBackground + excesoSprite;
	const float escalaY = windowSizeAlto / altoSpriteBackground + excesoSprite;

	size_t level;
	
	sf::Texture texturaFondoUlt;
	sf::Sprite spriteFondoUlt;

public:
	BackGround() : 
		level(1), 
		velocidadX(0.f), 
		velocidadY(0.f),  
		posX(0.f),
		posY(0.f)
	{
		spriteFondoUlt.setPosition(0, 0);
		loadSprites();
	}
	
	~BackGround() {}
	
	void loadSprites() {

        if (!texturaFondoUlt.loadFromFile("spriteBackground.png")) {
            std::cerr << "Error al cargar la textura" << std::endl;
        }

        spriteFondoUlt.setTexture(texturaFondoUlt);
		spriteFondoUlt.setTextureRect(sf::IntRect(0, 0, windowSizeAncho, windowSizeAlto));
		//spriteFondoUlt.setScale(escalaX, escalaY);
    }
	
	void setPosiciones(float posX, float posY) {
		this->posX = posX;
		this->posY = posY;
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(spriteFondoUlt);
	}

	void update(float velocidadX, float velocidaY) {

		//std::cout << "moviendo" << std::endl;
		setPosiciones(velocidadX, velocidaY);
		//calcularPosicion();
		moverSprites();
	}
	
	void calcularPosicion() {
		if (velocidadX > 0) {
			posX += velocidadX;
		}
		else if (velocidadX < 0) {
			posX += velocidadX;
		}

		if (velocidadY < 0) {
			posY -= velocidadY;
		}
		else if (velocidadY > 0) {
			posY += velocidadY;
		}
	}
	void moverSprites() {
		spriteFondoUlt.setTextureRect(sf::IntRect(posX - windowSizeAncho / 2, 0, anchoSpriteBackground, altoSpriteBackground));
		spriteFondoUlt.setPosition(posX - windowSizeAncho / 2, posY - windowSizeAlto / 2);
	}
};

#endif
