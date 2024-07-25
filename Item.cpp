
#include "Item.h"

Item::Item(float x, float y) {

    // para rebote aleatorio
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    hitBox.setPosition(x, y);
    hitBox.setSize(sf::Vector2f(anchoHitbox, altoHitbox));
    hitBox.setFillColor(sf::Color::Black);
    
    velocidadX = 170.0f;
    velocidadY = 0.0f;
    deltaTime = 0;
    //loadSpriteSheet("sprite.png");

    this->rebote = std::rand() % 2;
}

Item::~Item() {}


void Item::applyGravity() {
    velocidadY += GRAVITY * deltaTime;
}


void Item::detectarPisoTecho(const std::vector<std::vector<int>>& map) {
    if ((hitBox.getPosition().y >= 0 && hitBox.getPosition().y + altoHitbox < numRows * cellSize) &&
        (hitBox.getPosition().x >= 0 && hitBox.getPosition().x + altoHitbox < numCols * cellSize)) {
        for (int i = hitBox.getPosition().y / cellSize; i < numRows; i++) {
            if ((map[i][hitBox.getPosition().x / cellSize] >= rangeBloqueBegin || map[i][(hitBox.getPosition().x + hitBox.getSize().x) / cellSize] >= rangeBloqueBegin) &&
                (map[i][hitBox.getPosition().x / cellSize] <= rangeBloqueEspecialEnd|| map[i][(hitBox.getPosition().x + hitBox.getSize().x) / cellSize] <= rangeBloqueEspecialEnd)) {
                PISO = i * cellSize;
                break;
            }
            else {
                PISO = 400.0f;
            }
        }

        for (int i = hitBox.getPosition().y / cellSize; i >= 0; i--) {
            if ((map[i][hitBox.getPosition().x / cellSize] >= rangeBloqueBegin || map[i][(hitBox.getPosition().x + hitBox.getSize().x) / cellSize] >= rangeBloqueBegin) &&
                (map[i][hitBox.getPosition().x / cellSize] <= rangeBloqueEspecialEnd || map[i][(hitBox.getPosition().x + hitBox.getSize().x) / cellSize] <= rangeBloqueEspecialEnd)) {
                TECHO = (i + 1) * cellSize;
                break;
            }
            else {
                TECHO = -1000.0f;
            }
        }
    }
}

void Item::detectarObjIzqDer(const std::vector<std::vector<int>>& map) {
    if ((hitBox.getPosition().y >= 0 && hitBox.getPosition().y + altoHitbox < numRows * cellSize) &&
        (hitBox.getPosition().x >= 0 && hitBox.getPosition().x + anchoHitbox < numCols * cellSize)) {

        // Detección a la derecha
        for (int i = hitBox.getPosition().x / cellSize; i < numCols; i++) {
            if ((map[hitBox.getPosition().y / cellSize][i] >= rangeBloqueBegin || map[(hitBox.getPosition().y + altoHitbox) / cellSize][i] >= rangeBloqueBegin) &&
                (map[hitBox.getPosition().y / cellSize][i] <= rangeBloqueEspecialEnd || map[(hitBox.getPosition().y + altoHitbox) / cellSize][i] <= rangeBloqueEspecialEnd)) {
                OBJDER = i * cellSize;
                break;
            }
            else {
                OBJDER = numCols * cellSize;
            }
        }

        // Detección a la izquierda
        for (int i = hitBox.getPosition().x / cellSize; i >= 0; i--) {
            if ((map[hitBox.getPosition().y / cellSize][i] >= rangeBloqueBegin || map[(hitBox.getPosition().y + altoHitbox) / cellSize][i] >= rangeBloqueBegin) &&
                (map[hitBox.getPosition().y / cellSize][i] <= rangeBloqueEspecialEnd || map[(hitBox.getPosition().y + altoHitbox) / cellSize][i] <= rangeBloqueEspecialEnd)) {
                OBJIZQ = (i + 1) * cellSize;
                break;
            }
            else {
                OBJIZQ = 0;
            }
        }
    }
}


void Item::controlarMovimientoVertical(const std::vector<std::vector<int>>& map) {
    float nextMove = hitBox.getPosition().y + velocidadY * deltaTime;

    if (nextMove < TECHO) {
        nextMove = TECHO;
        velocidadY = 0;
        
    }

    hitBox.move(0.f, nextMove - hitBox.getPosition().y);

    if (hitBox.getPosition().y + altoHitbox > PISO) {
        hitBox.setPosition(hitBox.getPosition().x, PISO - altoHitbox - 1.0f);
        velocidadY = 0.0f;
    }

}


void Item::controlarMovimientoHorizontal(float deltaTime, const std::vector<std::vector<int>>& map) {

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


void Item::drawTo(sf::RenderWindow& window) {
    window.draw(hitBox);
    //window.draw(spriteItem);
}

void Item::update(float deltaTime, const std::vector<std::vector<int>>& map) {
    this->deltaTime = deltaTime;

    detectarObjIzqDer(map);
    detectarPisoTecho(map);

    applyGravity();

    controlarMovimientoHorizontal(deltaTime, map);
    
    controlarMovimientoVertical(map);

    //moverHorizontalSprite(left, right);
}
//
//
sf::RectangleShape Item::getHitBox() {
    return hitBox;
}


