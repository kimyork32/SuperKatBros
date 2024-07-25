#include "Aguila.h"

Aguila::Aguila() : Enemigo(), maxRecorridoDer(0.f), maxRecorridoIzq(0.f), yCentro(0.f) {}


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

void Aguila::setYCentro(float yCentro) {
    this->yCentro = yCentro;
}
void Aguila::setMaxRecorridoDer(float maxRecorridoDer) {
    this->maxRecorridoDer = maxRecorridoDer;
}
void Aguila::setMaxRecorridoIzq(float maxRecorridoIzq) {
    this->maxRecorridoIzq = maxRecorridoIzq;
}
