
#include "Item.h"

Item::Item(float x, float y) {
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

Item::~Item() {
    std::cout << "Item muerto" << std::endl;
}


void Item::applyGravity() {
    velocidadY += GRAVITY * deltaTime;
}


void Item::detectarPisoTecho(const std::vector<std::vector<int>>& map) {
    if ((hitBox.getPosition().y >= 0 && hitBox.getPosition().y + altoHitbox < numRows * cellSize) &&
        (hitBox.getPosition().x >= 0 && hitBox.getPosition().x + altoHitbox < numCols * cellSize)) {
        for (int i = hitBox.getPosition().y / cellSize; i < numRows; i++) {
            if ((map[i][hitBox.getPosition().x / cellSize] >= rangeBloqueBegin || map[i][(hitBox.getPosition().x + hitBox.getSize().x) / cellSize] >= rangeBloqueBegin) &&
                (map[i][hitBox.getPosition().x / cellSize] <= rangeBloqueEnd + 3 || map[i][(hitBox.getPosition().x + hitBox.getSize().x) / cellSize] <= rangeBloqueEnd + 3)) {
                PISO = i * cellSize;
                break;
            }
            else {
                PISO = 400.0f;
            }
        }

        for (int i = hitBox.getPosition().y / cellSize; i >= 0; i--) {
            if ((map[i][hitBox.getPosition().x / cellSize] >= rangeBloqueBegin || map[i][(hitBox.getPosition().x + hitBox.getSize().x) / cellSize] >= rangeBloqueBegin) &&
                (map[i][hitBox.getPosition().x / cellSize] <= rangeBloqueEnd + 3 || map[i][(hitBox.getPosition().x + hitBox.getSize().x) / cellSize] <= rangeBloqueEnd + 3)) {
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
                (map[hitBox.getPosition().y / cellSize][i] <= rangeBloqueEnd + 3 || map[(hitBox.getPosition().y + altoHitbox) / cellSize][i] <= rangeBloqueEnd + 3)) {
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
                (map[hitBox.getPosition().y / cellSize][i] <= rangeBloqueEnd + 3 || map[(hitBox.getPosition().y + altoHitbox) / cellSize][i] <= rangeBloqueEnd + 3)) {
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
        teclaSuelta = true;
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
    window.draw(spriteItem);
}

sf::Vector2f Item::getPosition() const {
    return hitBox.getPosition();
}

void Item::loadSpriteSheet(const std::string& filename) {
    if (!texturaItem.loadFromFile(filename)) {
        std::cerr << "Error cargando la textura" << std::endl;
        return;
    }
    spriteItem.setTexture(texturaItem);
    spriteItem.setTextureRect(sf::IntRect(0, 0, anchoSprite, altoSprite));
    spriteItem.setScale(escalaX, escalaY);
}

void Item::moverHorizontalSprite(bool left, bool right) {
    if (!stop) {
        if (rebote) {
            yTexture = (int(spriteItem.getPosition().x) / velocidadSprite) % 3 * altoSprite;
            spriteItem.setTextureRect(sf::IntRect(anchoSprite, yTexture, anchoSprite, altoSprite));
        }
        if (!rebote) {
            yTexture = (int(spriteItem.getPosition().x) / velocidadSprite) % 3 * altoSprite;
            spriteItem.setTextureRect(sf::IntRect(anchoSprite * 3, yTexture, anchoSprite, altoSprite));
        }
    }
    else {
        spriteItem.setTextureRect(sf::IntRect(0, 0, anchoSprite, altoSprite));
    }

    spriteItem.setPosition(hitBox.getPosition().x - ((anchoSprite * escalaX - anchoHitbox) / 2), hitBox.getPosition().y - ((altoSprite * escalaY - altoHitbox) / 2));

}


void Item::update(float deltaTime, const std::vector<std::vector<int>>& map) {
    this->deltaTime = deltaTime;

    detectarObjIzqDer(map);
    detectarPisoTecho(map);

    applyGravity();

    controlarMovimientoHorizontal(deltaTime, map);
    //controlarMovimientoVertical(map);
    moverHorizontalSprite(left, right);
}


sf::RectangleShape Item::getHitBox() {
    return hitBox;
}

float Item::getAnchoHitbox() {
    return anchoHitbox;
}

float Item::getAltoHitbox() {
    return altoHitbox;
}

float Item::getPosX() {
    return hitBox.getPosition().x;
}

float Item::getPosY() {
    return hitBox.getPosition().y;
}

//void Item::setVelocidadX(float velocidadX) {
//    this->velocidadX = velocidadX;
//}

void Item::parar() {
    this->stop = true;
}


