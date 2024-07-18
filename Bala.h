#pragma once
#ifndef BALA_H
#define BALA_H
#include <SFML/Graphics.hpp>
#include "Definitions.hpp"

class Bala {
private:
	bool direccionIzq;
	float velocidadX;
	float radio = 10.0f;
	float OBJIZQ = -1.0f;
	float OBJDER = -1.0f;
	float altoHitbox;
	float anchoHitbox;
	sf::CircleShape hitbox;
	sf::Clock relojVida;


public:
	Bala(int, int, bool);

	void setVelocidadX(float);

	void setRadio(float);

	void moverX(float);

	bool verificarTiempoVida();

	sf::CircleShape getHitBox();

	float getPosX();

	float getPosY();

	void detectarObjIzqDer(const std::vector<std::vector<int>>&);

	void update(float deltaTime, const std::vector<std::vector<int>>&);

	void drawTo(sf::RenderWindow&);

};


#endif
