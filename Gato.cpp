 #include "Gato.h"

Gato::Gato(float x, float y) {
    hitBox.setPosition(x, y);
	hitBox.setSize(sf::Vector2f(anchoHitbox, altoHitbox));
    hitBox.setFillColor(sf::Color::Red);

    this->monedas = 0;

    this->left = false;
    this->right = false;

    this->spacePressed = false;
    this->jumpButtonPressed = false;
    this->teclaSuelta = false;

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
    if (getPosY() + 1 >= PISO.y - altoHitbox) {
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
    if ((getPosY() >= 0 && getPosY() + altoHitbox < numRows * cellSize) &&
        (getPosX() >= 0 && getPosX() + altoHitbox < numCols * cellSize)) {
        for (int i = getPosY() / cellSize; i < numRows; i++) {
            //if (map[i][getPosX() / cellSize] != 0 || map[i][(getPosX() + hitBox.getSize().x) / cellSize] != 0) {
            if ((map[i][getPosX() / cellSize] >= rangeBloqueBegin || map[i][(getPosX() + hitBox.getSize().x) / cellSize] >= rangeBloqueBegin) &&
                (map[i][getPosX() / cellSize] <= rangeBloqueEspecialEnd || map[i][(getPosX() + hitBox.getSize().x) / cellSize] <= rangeBloqueEspecialEnd)) {
                PISO.y = i * cellSize;

                PISO.x = getPosX() + anchoHitbox / 2;
                break;
            }
            else {
                PISO.y = 400.0f;
                PISO.x = getPosX() + anchoHitbox / 2;
            }
        }

        for (int i = getPosY() / cellSize; i >= 0; i--) {
            //if (map[i][getPosX() / cellSize] != 0 || map[i][(getPosX() + hitBox.getSize().x) / cellSize] != 0){
            if ((map[i][getPosX() / cellSize] >= rangeBloqueBegin || map[i][(getPosX() + hitBox.getSize().x) / cellSize] >= rangeBloqueBegin) &&
                (map[i][getPosX() / cellSize] <= rangeBloqueEspecialEnd || map[i][(getPosX() + hitBox.getSize().x) / cellSize] <= rangeBloqueEspecialEnd)) {

                //std::cout << map[i][getPosY() / cellSize] << " " << map[i][(getPosX() + hitBox.getSize().x) / cellSize] << std::endl;

                TECHO.y = (i + 1) * cellSize;
                TECHO.x = getPosX() + anchoHitbox / 2;
                break;
            }
            else {
                TECHO.y = -1000.0f;
            }
        }
    }
}

void Gato::detectarObjIzqDer(const std::vector<std::vector<int>>& map) {
    if ((getPosY() >= 0 && getPosY() + altoHitbox < numRows * cellSize) &&
        (getPosX() >= 0 && getPosX() + anchoHitbox < numCols * cellSize)) {

        // Detección a la derecha
        for (int i = getPosX() / cellSize; i < numCols; i++) {
            //if (map[getPosY() / cellSize][i] != 0 || map[(getPosY() + altoHitbox) / cellSize][i] != 0) {
            if ((map[getPosY() / cellSize][i] >= rangeBloqueBegin || map[(getPosY() + altoHitbox) / cellSize][i] >= rangeBloqueBegin) &&
                (map[getPosY() / cellSize][i] <= rangeBloqueEspecialEnd || map[(getPosY() + altoHitbox) / cellSize][i] <= rangeBloqueEspecialEnd)) {
                
                //std::cout << map[getPosY() / cellSize][i] << " " << map[(getPosY() + altoHitbox)/ cellSize][i] << std::endl;

                OBJDER.x = i * cellSize;
				OBJDER.y = getPosY() + altoHitbox / 2;
                break;
            }
            else {
                OBJDER.x = numCols * cellSize;
            }
        }

        // Detección a la izquierda
        for (int i = getPosX() / cellSize; i >= 0; i--) {
            //if (map[getPosY() / cellSize][i] != 0 || map[(getPosY() + altoHitbox) / cellSize][i] != 0) {
            if ((map[getPosY() / cellSize][i] >= rangeBloqueBegin || map[(getPosY() + altoHitbox) / cellSize][i] >= rangeBloqueBegin) && 
                (map[getPosY() / cellSize][i] <= rangeBloqueEspecialEnd || map[(getPosY() + altoHitbox) / cellSize][i] <= rangeBloqueEspecialEnd)) {


                OBJIZQ.x = (i + 1) * cellSize;
				OBJIZQ.y = getPosY() + altoHitbox / 2;
                break;
            }
            else {
                OBJIZQ.x = 0;
            }
        }
    }
}


void Gato::controlarMovimientoVertical(const std::vector<std::vector<int>>& map) {
    float nextMove = getPosY() + velocidadY * deltaTime;
    if (nextMove < TECHO.y) {
        collideWithBlock(static_cast<int>(TECHO.x / cellSize), static_cast<int>(TECHO.y / cellSize) - 1.0f);
        nextMove = TECHO.y;
        velocidadY = 0;
        teclaSuelta = true;
    }

    hitBox.move(0.f, nextMove - getPosY());

    if (getPosY() + altoHitbox > PISO.y) {
        //collideWithBlock(static_cast<int>(PISO.x / cellSize), static_cast<int>(PISO.y / cellSize));
        hitBox.setPosition(getPosX(), PISO.y - altoHitbox - 1.0f);
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
        std::cout << OBJDER.x << " " << getPosX() + anchoHitbox + proxMovimientoX << std::endl;
        if (getPosX() + anchoHitbox + proxMovimientoX > OBJDER.x) {
			//collideWithBlock(static_cast<int>(OBJDER.x / cellSize), static_cast<int>(OBJDER.y / cellSize));
			proxMovimientoX = OBJDER.x - getPosX() - anchoHitbox - 1.0f;
            std::cout << "stop der " << std::endl;
        }
       
        else if (getPosX() + proxMovimientoX < OBJIZQ.x) {
            //collideWithBlock(static_cast<int>(OBJIZQ.x / cellSize) - 1.0f, static_cast<int>(OBJIZQ.y / }cellSize));
            proxMovimientoX = OBJIZQ.x - getPosX() + 1.0f;
            std::cout << "stop izq" << std::endl;
        }
        else {
            hitBox.move(proxMovimientoX, 0.f);
        }
        
    }
    
}


void Gato::drawTo(sf::RenderWindow& window) {
    //window.draw(hitBox);
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
    spriteGato.setPosition(getPosX() - ((anchoSprite * escalaX - anchoHitbox) / 2), getPosY() - ((altoSprite * escalaY - altoHitbox) / 2));
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

    //std::cout << "objD: " << OBJDER.x << " " << OBJDER.y << " objI: " << OBJIZQ.x << " " << OBJIZQ.y << std::endl;
    //std::cout << "piso: " << PISO.y << " " << PISO.y << " techo: " << TECHO.x << " " << TECHO.y << std::endl;

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
	hitBox.move(esquinaIzqObj - getPosX() - anchoHitbox - 1.0f, 0);
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

void Gato::setVelocidadX(float velocidadX) {
    this->velocidadX = velocidadX;
}

void Gato::aumentarVelocidadX(float velocidadPlus) {
    if (!isAumentarVelocidadUsado) {
        this->velocidadX = this->velocidadX + velocidadPlus;
        isAumentarVelocidadUsado = true;
    }
}

float Gato::getVelocidadX() {
    return velocidadX;
}

unsigned int Gato::getMonedas() {
    return monedas;
}

void Gato::aumentarMonedas() {
    this-> monedas += 1;
}

void Gato::crearBala() {
    balas.push_back(std::make_unique<Bala>(getPosX() + anchoHitbox / 2, getPosY() + altoHitbox / 2, left));
}