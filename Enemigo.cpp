#include "Enemigo.h"

Enemigo::Enemigo(float x, float y) {
    hitBox.setPosition(x, y);
    hitBox.setSize(sf::Vector2f(anchoHitbox, altoHitbox));
    hitBox.setFillColor(sf::Color::Red);

    velocidadX = 170.0f;
    velocidadY = 0.0f;

    left = false;
    right = false;

    spacePressed = false;
    jumpButtonPressed = false;
    teclaSuelta = false;

    deltaTime = 0;
    jumpTime = 0.0f;
    loadSpriteSheet("sprite.png");
}

Enemigo::~Enemigo() {
    std::cout << "enemigo muerto" << std::endl;
}

//void Enemigo::saltar() {
//    if (hitBox.getPosition().y + 1 >= PISO - altoHitbox) {
//        velocidadY = JUMP_FORCE / MASS;
//        jumpTime = 0.0f;
//    }
//}

//void Enemigo::controlarSalto() {
//    this->jumpButtonPressed = static_cast<bool>(spacePressed && clock2.getElapsedTime().asMilliseconds() < 800 && !teclaSuelta);
//
//    if (jumpButtonPressed) {
//        saltar();
//        jumpTime += deltaTime;
//        velocidadY += (JUMP_FORCE / MASS) * deltaTime / MAX_JUMP_TIME;
//    }
//}

void Enemigo::applyGravity() {
    velocidadY += GRAVITY * deltaTime;
}


void Enemigo::detectarPisoTecho(const std::vector<std::vector<int>>& map) {
    if ((hitBox.getPosition().y >= 0 && hitBox.getPosition().y + altoHitbox < numRows * cellSize) &&
        (hitBox.getPosition().x >= 0 && hitBox.getPosition().x + altoHitbox < numCols * cellSize)) {
        for (int i = hitBox.getPosition().y / cellSize; i < numRows; i++) {
            if (map[i][hitBox.getPosition().x / cellSize] != 0 || map[i][(hitBox.getPosition().x + hitBox.getSize().x) / cellSize] != 0) {
                PISO = i * cellSize;
                break;
            }
            else {
                PISO = 400.0f;
            }
        }

        for (int i = hitBox.getPosition().y / cellSize; i >= 0; i--) {
            if (map[i][hitBox.getPosition().x / cellSize] != 0 || map[i][(hitBox.getPosition().x + hitBox.getSize().x) / cellSize] != 0) {
                TECHO = (i + 1) * cellSize;
                break;
            }
            else {
                TECHO = -1000.0f;
            }
        }
    }
}

void Enemigo::detectarObjIzqDer(const std::vector<std::vector<int>>& map) {
    if ((hitBox.getPosition().y >= 0 && hitBox.getPosition().y + altoHitbox < numRows * cellSize) &&
        (hitBox.getPosition().x >= 0 && hitBox.getPosition().x + anchoHitbox < numCols * cellSize)) {

        // Detección a la derecha
        for (int i = hitBox.getPosition().x / cellSize; i < numCols; i++) {
            if (map[hitBox.getPosition().y / cellSize][i] != 0 || map[(hitBox.getPosition().y + altoHitbox) / cellSize][i] != 0) {
                OBJDER = i * cellSize;
                break;
            }
            else {
                OBJDER = numCols * cellSize;
            }
        }

        // Detección a la izquierda
        for (int i = hitBox.getPosition().x / cellSize; i >= 0; i--) {
            if (map[hitBox.getPosition().y / cellSize][i] != 0 || map[(hitBox.getPosition().y + altoHitbox) / cellSize][i] != 0) {
                OBJIZQ = (i + 1) * cellSize;
                break;
            }
            else {
                OBJIZQ = 0;
            }
        }
    }
}


void Enemigo::controlarMovimientoVertical(const std::vector<std::vector<int>>& map) {
    float nextMove = hitBox.getPosition().y + velocidadY * deltaTime;

    if (nextMove < TECHO) {
        nextMove = TECHO;
        velocidadY = 0;
        teclaSuelta = true;
    }

    hitBox.move(0.f, nextMove - hitBox.getPosition().y);

    if (hitBox.getPosition().y + altoHitbox > PISO) {
        hitBox.setPosition(hitBox.getPosition().x, PISO - altoHitbox - 1.0f);
        velocidadY = 0.0f;
    }

}


void Enemigo::controlarMovimientoHorizontal(float deltaTime, const std::vector<std::vector<int>>& map) {

    float proxMovimientoX = 0.0f;

    if (!stop) {
        if (rebote)
            proxMovimientoX -= velocidadX * deltaTime;
        else if (!rebote)
            proxMovimientoX += velocidadX * deltaTime;
    }


    if (proxMovimientoX != 0) {

        if (hitBox.getPosition().x + anchoHitbox + proxMovimientoX > OBJDER) {
            proxMovimientoX = OBJDER - hitBox.getPosition().x - anchoHitbox - 1.0f;
            rebote = !rebote; 
        }

        else if (hitBox.getPosition().x + proxMovimientoX < OBJIZQ) {
            proxMovimientoX = OBJIZQ - hitBox.getPosition().x + 1.0f;
            rebote = !rebote;
        }
        else {
            hitBox.move(proxMovimientoX, 0.f);
        }

    }

}


void Enemigo::drawTo(sf::RenderWindow& window) {
    window.draw(hitBox);
    window.draw(spriteGato);
}

sf::Vector2f Enemigo::getPosition() const {
    return hitBox.getPosition();
}

void Enemigo::loadSpriteSheet(const std::string& filename) {
    if (!texturaGato.loadFromFile(filename)) {
        std::cerr << "Error cargando la textura" << std::endl;
        return;
    }
    spriteGato.setTexture(texturaGato);
    spriteGato.setTextureRect(sf::IntRect(0, 0, anchoSprite, altoSprite));
    spriteGato.setScale(escalaX, escalaY);
}

void Enemigo::moverHorizontalSprite(bool left, bool right) {
    if (!stop) {
        if (rebote) {
            yTexture = (int(spriteGato.getPosition().x) / velocidadSprite) % 3 * altoSprite;
            spriteGato.setTextureRect(sf::IntRect(anchoSprite, yTexture, anchoSprite, altoSprite));
        }
        if (!rebote) {
            yTexture = (int(spriteGato.getPosition().x) / velocidadSprite) % 3 * altoSprite;
            spriteGato.setTextureRect(sf::IntRect(anchoSprite * 3, yTexture, anchoSprite, altoSprite));
        }
    }
    else {
        spriteGato.setTextureRect(sf::IntRect(0, 0, anchoSprite, altoSprite));
    }
    
    spriteGato.setPosition(hitBox.getPosition().x - ((anchoSprite * escalaX - anchoHitbox) / 2), hitBox.getPosition().y - ((altoSprite * escalaY - altoHitbox) / 2));

}


void Enemigo::update(float deltaTime, const std::vector<std::vector<int>>& map) {
    this->deltaTime = deltaTime;

    detectarObjIzqDer(map);
    detectarPisoTecho(map);

    //controlarSalto();
    applyGravity();

    controlarMovimientoHorizontal(deltaTime, map);
    controlarMovimientoVertical(map);
    moverHorizontalSprite(left, right);
}


sf::RectangleShape Enemigo::getHitBox() {
	return hitBox;
}

float Enemigo::getAnchoHitbox() {
	return anchoHitbox;
}

float Enemigo::getAltoHitbox() {
	return altoHitbox;
}

float Enemigo::getPosX() {
    return hitBox.getPosition().x;
}

float Enemigo::getPosY() {
    return hitBox.getPosition().y;
}

//void Enemigo::setVelocidadX(float velocidadX) {
//    this->velocidadX = velocidadX;
//}

void Enemigo::parar() {
    this->stop = true;
}

