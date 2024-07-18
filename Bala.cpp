#include "Bala.h"

Bala::Bala(int x, int y, bool direccionIzq) : direccionIzq(direccionIzq), velocidadX(200.0f) {
    //this->radio = anchoHitbox;
    this->altoHitbox = 5.0f;
    this->anchoHitbox = 5.0f;
    hitbox.setPosition(x, y);
    hitbox.setRadius(radio);
    hitbox.setFillColor(sf::Color::Red);
}

void Bala::setVelocidadX(float velocidadX) {
	this->velocidadX = velocidadX;
}

void Bala::setRadio(float radio) {
	this->radio = radio;
}

void Bala::moverX(float deltaTime) {

    float proxMovimientoX = 0.0f;
    if (direccionIzq)
        proxMovimientoX -= velocidadX * deltaTime;
    else if (!direccionIzq)
        proxMovimientoX += velocidadX * deltaTime;
    
    if (proxMovimientoX != 0) {
      
      hitbox.move(proxMovimientoX, 0.f);
      

    }
}

bool Bala::verificarTiempoVida() {
	float tiempoVida = relojVida.getElapsedTime().asSeconds();

	if (tiempoVida > 2.0f) {
        return true;
    }
    return false;
}


sf::CircleShape Bala::getHitBox() {
	return hitbox;
}

float Bala::getPosX() {
	return hitbox.getPosition().x;
}

float Bala::getPosY() {
	return hitbox.getPosition().y;
}

void Bala::detectarObjIzqDer(const std::vector<std::vector<int>>& map) {
    if ((getPosY() >= 0 && getPosY() + altoHitbox < numRows * cellSize) &&
        (getPosX() >= 0 && getPosX() + anchoHitbox < numCols * cellSize)) {

        // Detección a la derecha
        for (int i = getPosX() / cellSize; i < numCols; i++) {
            if (map[getPosY() / cellSize][i] != 0 || map[(getPosY() + altoHitbox) / cellSize][i] != 0) {
                OBJDER = i * cellSize;
                break;
            }
            else {
                OBJDER = numCols * cellSize;
            }
        }

        // Detección a la izquierda
        for (int i = getPosX() / cellSize; i >= 0; i--) {
            if (map[getPosY() / cellSize][i] != 0 || map[(getPosY() + altoHitbox) / cellSize][i] != 0) {
                OBJIZQ = (i + 1) * cellSize;
                break;
            }
            else {
                OBJIZQ = 0;
            }
        }
    }
}

void Bala::update(float deltaTime, const std::vector<std::vector<int>>& map) {
	moverX(deltaTime);
    detectarObjIzqDer(map);
}

void Bala::drawTo(sf::RenderWindow& window) {
    window.draw(hitbox);
    //window.draw(spriteGato);
}