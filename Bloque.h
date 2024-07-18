#pragma once
#ifndef BLOQUE_H
#define BLOQUE_H

#include "SFML\Graphics.hpp"
#include "Definitions.hpp"
#include "ObserverColision.h"
#include "Mapa.h"


#include <iostream>
#include <string>


class Bloque : public ObserverColision {
protected:
	sf::RectangleShape hitBox;
	float anchoHitbox = static_cast<float>(cellSize);
	float altoHitbox = static_cast<float>(cellSize);
	bool colisionDetect = false;
	unsigned int vidas;
	//std::string type;
	
public:

	bool colisionArriba = false;
	bool colisionAbajo = false;
	bool colisionLadoIzq = false;
	bool colisionLadoDer = false;


	Bloque(float, float);

	sf::RectangleShape getHitBox();
	void drawTo(sf::RenderWindow&);
	float getAnchoHitbox();
	float getAltoHitbox();
	float getPosX();
	float getPosY();
	void onNotify(int, int) override;
	bool verificarColision();
	void setColisionDetect(bool);
	void disminuirVida();
	unsigned int getVidas();
	std::string getType();
};

#endif // !BLOQUE_H

