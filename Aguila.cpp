#include "Aguila.h"

Aguila::Aguila(float x, float y) : Enemigo(x, y) {
    this->maxRecorridoDer = getPosX() + (6 * cellSize);
    this->maxRecorridoIzq = getPosX() - ((6 + 1) * cellSize);
    //this->PISO = y + cellSize;
    this->yCentro = y + altoHitbox / 2;
    loadSpriteSheet("sprite.png");
}

Aguila::Aguila(const Aguila& other) :
    Enemigo(other),
    verificarMoverseMismaPlataforma(other.verificarMoverseMismaPlataforma),
    maxRecorridoIzq(other.maxRecorridoIzq),
    maxRecorridoDer(other.maxRecorridoDer),
    yCentro(other.yCentro),
    amplitud(other.amplitud),
    frecuencia(other.frecuencia),
    fase(other.fase),
    relojOscilacion(other.relojOscilacion) {}

void Aguila::update(float deltaTime, const std::vector<std::vector<int>>& map) {
    this->deltaTime = deltaTime;
    detectarPiso(map, this->PISO);
    detectarTecho(map);
    if (!verificarMoverseMismaPlataforma) {
        detectarObjDer(map);
        detectarObjIzq(map);
    }

    applyGravity();
    determinarVuelo();
    determinarExtremosX();
    controlarMovimientoHorizontal(deltaTime);
    //controlarMovimientoVertical();
    moverHorizontalSprite(left, right);
}

void Aguila::determinarExtremosX() {
    if (getPosX() >= maxRecorridoDer || getPosX() <= maxRecorridoIzq) {
        rebote = !rebote;
    }
}

void Aguila::determinarVuelo() {
    // Calcula la nueva posición en y usando la fórmula de oscilación
    float tiempo = relojOscilacion.getElapsedTime().asSeconds();
    float nuevaY = yCentro + amplitud * std::sin(2 * M_PI * frecuencia * tiempo + fase);


    hitBox.move(0, nuevaY - getPosY());
    
}

std::unique_ptr<CloneableEnemigo> Aguila::clone(int newX, int newY) const {
    return std::make_unique<Aguila>(newX, newY);
}