 #include "Gato.h"

Gato::Gato(float x, float y) {
    hitBox.setPosition(x, y);
	hitBox.setSize(sf::Vector2f(anchoHitbox, altoHitbox));
    hitBox.setFillColor(sf::Color::Red);

    velocidadX = 320.0f;
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

void Gato::processEvents(const sf::Event& event) {

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left)
            left = true;
        if (event.key.code == sf::Keyboard::Right)
            right = true;
        if (event.key.code == sf::Keyboard::Space && !spacePressed) {
            spacePressed = true;
            clock2.restart();
        }
    }
    else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Left)
            left = false;
        if (event.key.code == sf::Keyboard::Right)
            right = false;
        if (event.key.code == sf::Keyboard::Space) {
            spacePressed = false;
            teclaSuelta = false;
        }
    }
}

void Gato::saltar() {
    if (hitBox.getPosition().y + 1 >= PISO.y - altoHitbox) {
        velocidadY = JUMP_FORCE / MASS;
        jumpTime = 0.0f;
    }
    jumpTime += deltaTime;
    velocidadY += (JUMP_FORCE / MASS) * deltaTime / MAX_JUMP_TIME;  
}

void Gato::controlarSalto() {
    this->jumpButtonPressed = static_cast<bool>(spacePressed && clock2.getElapsedTime().asMilliseconds() < 800 && !teclaSuelta);

    if (jumpButtonPressed) {
        saltar();
        
    }
}

void Gato::applyGravity() {
    velocidadY += GRAVITY * deltaTime;
}




void Gato::detectarPisoTecho(const std::vector<std::vector<int>>& map) {
    if ((hitBox.getPosition().y >= 0 && hitBox.getPosition().y + altoHitbox < numRows * cellSize) &&
        (hitBox.getPosition().x >= 0 && hitBox.getPosition().x + altoHitbox < numCols * cellSize)) {
        for (int i = hitBox.getPosition().y / cellSize; i < numRows; i++) {
            if (map[i][hitBox.getPosition().x / cellSize] != 0 || map[i][(hitBox.getPosition().x + hitBox.getSize().x) / cellSize] != 0) {
                PISO.y = i * cellSize;

                PISO.x = hitBox.getPosition().x + anchoHitbox / 2;
                break;
            }
            else {
                PISO.y = 400.0f;
            }
        }

        for (int i = hitBox.getPosition().y / cellSize; i >= 0; i--) {
            if (map[i][hitBox.getPosition().x / cellSize] != 0 || map[i][(hitBox.getPosition().x + hitBox.getSize().x) / cellSize] != 0){
                TECHO.y = (i + 1) * cellSize;
                TECHO.x = hitBox.getPosition().x + anchoHitbox / 2;
                break;
            }
            else {
                TECHO.y = -1000.0f;
            }
        }
    }
}

void Gato::detectarObjIzqDer(const std::vector<std::vector<int>>& map) {
    if ((hitBox.getPosition().y >= 0 && hitBox.getPosition().y + altoHitbox < numRows * cellSize) &&
        (hitBox.getPosition().x >= 0 && hitBox.getPosition().x + anchoHitbox < numCols * cellSize)) {

        // Detección a la derecha
        for (int i = hitBox.getPosition().x / cellSize; i < numCols; i++) {
            if (map[hitBox.getPosition().y / cellSize][i] != 0 || map[(hitBox.getPosition().y + altoHitbox) / cellSize][i] != 0) {
                OBJDER.x = i * cellSize;
				OBJDER.y = hitBox.getPosition().y + altoHitbox / 2;
                break;
            }
            else {
                OBJDER.x = numCols * cellSize;
            }
        }

        // Detección a la izquierda
        for (int i = hitBox.getPosition().x / cellSize; i >= 0; i--) {
            if (map[hitBox.getPosition().y / cellSize][i] != 0 || map[(hitBox.getPosition().y + altoHitbox) / cellSize][i] != 0) {
                OBJIZQ.x = (i + 1) * cellSize;
				OBJIZQ.y = hitBox.getPosition().y + altoHitbox / 2;
                break;
            }
            else {
                OBJIZQ.x = 0;
            }
        }
    }
}


void Gato::controlarMovimientoVertical(const std::vector<std::vector<int>>& map) {
    float nextMove = hitBox.getPosition().y + velocidadY * deltaTime;
    if (nextMove < TECHO.y) {
        collideWithBlock(static_cast<int>(TECHO.x / cellSize), static_cast<int>(TECHO.y / cellSize) - 1.0f);
        nextMove = TECHO.y;
        velocidadY = 0;
        teclaSuelta = true;
    }

    hitBox.move(0.f, nextMove - hitBox.getPosition().y);

    if (hitBox.getPosition().y + altoHitbox > PISO.y) {
        //collideWithBlock(static_cast<int>(PISO.x / cellSize), static_cast<int>(PISO.y / cellSize));
        hitBox.setPosition(hitBox.getPosition().x, PISO.y - altoHitbox - 1.0f);
        velocidadY = 0.0f;
    }
}


void Gato::controlarMovimientoHorizontal(float deltaTime, const std::vector<std::vector<int>>& map) {
    
    float proxMovimientoX = 0.0f;

    if (left && !stopIzq) {

        proxMovimientoX -= velocidadX * deltaTime;
    }
    if (right && !stopDer) {
        proxMovimientoX += velocidadX * deltaTime;
    }
    
    if (proxMovimientoX != 0) {
		
        if (hitBox.getPosition().x + anchoHitbox + proxMovimientoX > OBJDER.x) {
			//collideWithBlock(static_cast<int>(OBJDER.x / cellSize), static_cast<int>(OBJDER.y / cellSize));
			proxMovimientoX = OBJDER.x - hitBox.getPosition().x - anchoHitbox - 1.0f;
        }
       
        else if (hitBox.getPosition().x + proxMovimientoX < OBJIZQ.x) {
            //collideWithBlock(static_cast<int>(OBJIZQ.x / cellSize) - 1.0f, static_cast<int>(OBJIZQ.y / }cellSize));
            proxMovimientoX = OBJIZQ.x - hitBox.getPosition().x + 1.0f;
        }
        else {
            hitBox.move(proxMovimientoX, 0.f);
        }
        
    }
    
}


void Gato::drawTo(sf::RenderWindow& window) {
    window.draw(hitBox);
    window.draw(spriteGato);
}

sf::Vector2f Gato::getPosition() const {
    return hitBox.getPosition();
}

void Gato::loadSpriteSheet(const std::string& filename) {
    if (!texturaGato.loadFromFile(filename)) {
        std::cerr << "Error cargando la textura" << std::endl;
        return;
    }
    spriteGato.setTexture(texturaGato);
    spriteGato.setTextureRect(sf::IntRect(0, 0, anchoSprite, altoSprite));
    spriteGato.setScale(escalaX, escalaY);
}

void Gato::moverHorizontalSprite(bool left, bool right) {
    if (left) {
        yTexture = (int(spriteGato.getPosition().x) / velocidadSprite) % 3 * altoSprite;
        spriteGato.setTextureRect(sf::IntRect(anchoSprite, yTexture, anchoSprite, altoSprite));
    }
    if (right) {
        yTexture = (int(spriteGato.getPosition().x) / velocidadSprite) % 3 * altoSprite;
        spriteGato.setTextureRect(sf::IntRect(anchoSprite * 3, yTexture, anchoSprite, altoSprite));
    }
    if (!left && !right) {
        spriteGato.setTextureRect(sf::IntRect(0, 0, anchoSprite, altoSprite));
    }
    spriteGato.setPosition(hitBox.getPosition().x - ((anchoSprite * escalaX - anchoHitbox) / 2), hitBox.getPosition().y - ((altoSprite * escalaY - altoHitbox) / 2));
}


void Gato::update(float deltaTime, const std::vector<std::vector<int>>& map) {
    this->deltaTime = deltaTime;

    detectarObjIzqDer(map);
    detectarPisoTecho(map);

    controlarSalto();
    applyGravity();

    controlarMovimientoHorizontal(deltaTime, map);
    controlarMovimientoVertical(map);
    moverHorizontalSprite(left, right);
}

sf::RectangleShape Gato::getHitBox() {
	return hitBox;
}

float Gato::getAnchoHitbox() {
	return anchoHitbox;
}

float Gato::getAltoHitbox() {
	return altoHitbox;
}

float Gato::getPosX() {
	return hitBox.getPosition().x;
}

float Gato::getPosY() {
	return hitBox.getPosition().y;
}


void Gato::pararMovimientoXDer(float esquinaIzqObj) {
	hitBox.move(esquinaIzqObj - hitBox.getPosition().x - anchoHitbox - 1.0f, 0);
    spriteGato.setTextureRect(sf::IntRect(0, 0, anchoSprite, altoSprite));
}

void Gato::seguirMovimientoXDer() {
	this->stopDer = false;
}


void Gato::morir() {
    hitBox.setPosition(2 * cellSize, 2 * cellSize);
}

void Gato::collideWithBlock(int i, int j) {
    notify(i, j);
}
