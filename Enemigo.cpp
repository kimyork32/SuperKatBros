#include "Enemigo.h"

Enemigo::Enemigo(float x, float y) {
    hitBox.setPosition(x, y);
    hitBox.setSize(sf::Vector2f(anchoHitbox, altoHitbox));
    hitBox.setFillColor(sf::Color::Red);

    velocidadX = 170.0f;
    velocidadY = 0.0f;

    this->deteccionPiso = hitBox.getPosition();
    left = false;
    right = false;

    spacePressed = false;
    jumpButtonPressed = false;
    teclaSuelta = false;

    deltaTime = 0;
    jumpTime = 0.0f;    
}

void Enemigo::applyGravity() {
    velocidadY += GRAVITY * deltaTime;
}


void Enemigo::detectarPiso(const std::vector<std::vector<int>>& map, sf::Vector2f& PISO) {
    if ((getPosY() >= 0 && getPosY() + altoHitbox < numRows * cellSize) &&
        (getPosX() >= 0 && getPosX() + altoHitbox < numCols * cellSize)) {
        for (int i = getPosY() / cellSize; i < numRows; i++) {
            if ((map[i][getPosX() / cellSize] >= rangeBloqueBegin || map[i][(getPosX() + hitBox.getSize().x) / cellSize] >= rangeBloqueBegin) &&
                (map[i][getPosX() / cellSize] <= rangeBloqueEspecialEnd || map[i][(getPosX() + hitBox.getSize().x) / cellSize] <= rangeBloqueEspecialEnd)) {
                PISO.y = i * cellSize;
                PISO.x = static_cast<int>(getPosX() + anchoHitbox / 2);
                break;
            }
            else {
                PISO.y = 400.0f;
                PISO.x = static_cast<int>(getPosX() + anchoHitbox / 2);
            }
        }
        
    }
}

void Enemigo::detectarTecho(const std::vector<std::vector<int>>& map) {
    if ((getPosY() >= 0 && getPosY() + altoHitbox < numRows * cellSize) &&
        (getPosX() >= 0 && getPosX() + altoHitbox < numCols * cellSize)) {
        for (int i = getPosY() / cellSize; i >= 0; i--) {
            if ((map[i][getPosX() / cellSize] >= rangeBloqueBegin || map[i][(getPosX() + hitBox.getSize().x) / cellSize] >= rangeBloqueBegin) &&
                (map[i][getPosX() / cellSize] <= rangeBloqueEspecialEnd || map[i][(getPosX() + hitBox.getSize().x) / cellSize] <= rangeBloqueEspecialEnd)) {
                TECHO.y = (i + 1) * cellSize;
                TECHO.x = getPosX() + anchoHitbox / 2;
                break;
            }
            else {
                TECHO.y = -1000.0f;
                TECHO.x = getPosX() + anchoHitbox / 2;
            }
        }
    }
}


void Enemigo::detectarObjDer(const std::vector<std::vector<int>>& map) {
    if ((getPosY() >= 0 && getPosY() + altoHitbox < numRows * cellSize) &&
        (getPosX() >= 0 && getPosX() + anchoHitbox < numCols * cellSize)) {

        // Detección a la derecha
        for (int i = getPosX() / cellSize; i < numCols; i++) {
            if ((map[getPosY() / cellSize][i] >= rangeBloqueBegin || map[(getPosY() + altoHitbox) / cellSize][i] >= rangeBloqueBegin) &&
                (map[getPosY() / cellSize][i] <= rangeBloqueEspecialEnd || map[(getPosY() + altoHitbox) / cellSize][i] <= rangeBloqueEspecialEnd)) {
                OBJDER = i * cellSize;
                break;
            }
            else {
                OBJDER = numCols * cellSize;
            }
        }
    }
}

void Enemigo::detectarObjIzq(const std::vector<std::vector<int>>& map) {
    if ((getPosY() >= 0 && getPosY() + altoHitbox < numRows * cellSize) &&
        (getPosX() >= 0 && getPosX() + anchoHitbox < numCols * cellSize)) {

        // Detección a la izquierda
        for (int i = getPosX() / cellSize; i >= 0; i--) {
            if ((map[getPosY() / cellSize][i] >= rangeBloqueBegin || map[(getPosY() + altoHitbox) / cellSize][i] >= rangeBloqueBegin) &&
                (map[getPosY() / cellSize][i] <= rangeBloqueEspecialEnd || map[(getPosY() + altoHitbox) / cellSize][i] <= rangeBloqueEspecialEnd)) {
                OBJIZQ = (i + 1) * cellSize;
                break;
            }
            else {
                OBJIZQ = 0;
            }
        }
    }
}


void Enemigo::controlarMovimientoVertical() {
    float nextMove = getPosY() + velocidadY * deltaTime;

    if (nextMove < TECHO.y) {
        nextMove = TECHO.y;
        velocidadY = 0;
        teclaSuelta = true;
    }

    hitBox.move(0.f, nextMove - getPosY());

    if (getPosY() + altoHitbox > PISO.y) {
        hitBox.setPosition(getPosX(), PISO.y - altoHitbox - 1.0f);
        velocidadY = 0.0f;
    }

}


void Enemigo::controlarMovimientoHorizontal(float deltaTime) {
    
    float proxMovimientoX = 0.0f;

    if (!stop) {
        if (rebote)
            proxMovimientoX -= velocidadX * deltaTime;
        else if (!rebote)
            proxMovimientoX += velocidadX * deltaTime;
    }

    if (proxMovimientoX != 0) {
        
        if (verificarMoverseMismaPlataforma) {
            if (PISO.y != pisoUnicoPlataforma.y) {
                rebote = !rebote;
            }
        }

        if (getPosX() + anchoHitbox + proxMovimientoX >= OBJDER) {
            proxMovimientoX = OBJDER - getPosX() - anchoHitbox - 1.0f;
            rebote = !rebote; 
        }

        else if (getPosX() + proxMovimientoX <= OBJIZQ) {
            proxMovimientoX = OBJIZQ - getPosX() + 1.0f;
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
    
    spriteGato.setPosition(getPosX() - ((anchoSprite * escalaX - anchoHitbox) / 2), getPosY() - ((altoSprite * escalaY - altoHitbox) / 2));

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


void Enemigo::parar() {
    this->stop = true;
}

void Enemigo::detectarOjbIzqDerPlataforma(const std::vector<std::vector<int>> map, int a) {
  
    int f = numRows;
    int c = numCols;

    int p=-1;
    int b = static_cast<int>(getPosY() / cellSize);
    for (int i = b + 1; i < f; i++) {

        if (map[i][a] != 0) {
            p = i;
            break;
        }
    }
    if (p > 0) {
        // IZQUIERDA
        for (int i = a - 1; i >= 0; i--) {
            if (map[p][i] != 0) {
                
                if (map[p - 1][i] != 0) {
                    this->OBJIZQ = i * cellSize;
                    break;
                }
            }
            else {
                this->OBJIZQ = (i + 1) * cellSize;
                break;
            }
        }

        // DERCHA
        for (int i = a + 1; i < c; i++) {
            if (map[p][i] != 0) {
                if (map[p - 1][i] != 0) {
                    this->OBJDER = (i + 1) * cellSize;
                    break;
                }
            }
            else {
                this->OBJDER = i * cellSize;
                break;
            }
        }
    }
}

void Enemigo::moverseMismaPlataforma(const std::vector<std::vector<int>> map) {
    detectarOjbIzqDerPlataforma(map, static_cast<int>(this->deteccionPiso.x/cellSize));
    detectarPiso(map, this->pisoUnicoPlataforma);
    this->verificarMoverseMismaPlataforma = true;
}

void Enemigo::detectarPisoRoto(const std::vector<std::vector<int>> map) {
    detectarPiso(map, this->deteccionPiso);
    if (deteccionPiso.y != pisoUnicoPlataforma.y) {
        this->pisoUnicoPlataforma = this->deteccionPiso;
        moverseMismaPlataforma(map);
    }
}
