#include "Bloque.h"

Bloque::Bloque(float x, float y) {
	hitBox.setPosition(x, y);
	hitBox.setSize(sf::Vector2f(anchoHitbox, altoHitbox));
}

void Bloque::drawTo(sf::RenderWindow& window) {
	window.draw(hitBox);
}

sf::RectangleShape Bloque::getHitBox() {
	return hitBox;
}

float Bloque::getAnchoHitbox() {
	return anchoHitbox;
}

float Bloque::getAltoHitbox() {
	return altoHitbox;
}

float Bloque::getPosX() {
	return hitBox.getPosition().x;
}

float Bloque::getPosY() {
	return hitBox.getPosition().y;
}

void Bloque::onNotify(int i, int j) {
	if ((i == getPosX()/cellSize) && (j==getPosY()/cellSize)) {
		std::cout << "B " << i << " " << j << " col" << std::endl;
		colisionDetect = true; 
	}
}

bool Bloque::verificarColision() {
	return colisionDetect;
}



