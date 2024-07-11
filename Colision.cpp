#include "Colision.h"

// colision con enemigos
void Colision::verificarColisionHitboxEnemigo(Gato* gato, std::vector<std::unique_ptr<Enemigo>>& enemigos) {
    for (size_t i = 0; i < enemigos.size(); /* no incrementar i aqu� */) {
        if (!enemigos[i]->getHitBox().getGlobalBounds().intersects(gato->getHitBox().getGlobalBounds())) {

            // Colision por arriba
            if (enemigos[i]->getPosX() + enemigos[i]->getAltoHitbox() + 1.0f > gato->getPosX() &&
                enemigos[i]->getPosX() < gato->getPosX() + gato->getAnchoHitbox() + 1.0f &&
                enemigos[i]->getPosY() >= gato->getPosY() + gato->getAltoHitbox()) {
                enemigos[i]->colisionLados = false;
            }

            // Colision por los lados
            if (enemigos[i]->getPosY() < gato->getPosY() + gato->getAltoHitbox() + 1.0f &&
                enemigos[i]->getPosY() + enemigos[i]->getAltoHitbox() + 1.0f > gato->getPosY()) {
                enemigos[i]->colisionLados = true;
            }

            // Incrementar i solo si no se elimina el elemento en este ciclo
            ++i;
        }
        else {
            if (enemigos[i]->colisionLados) { // player colisiona en los lados del enemigo -> player muere
                gato->morir();
            }
            else { // player colisiona por arriba del enemigo -> enemigo muere
                enemigos.erase(enemigos.begin() + i);
            }
            // No incrementar i aqu�, ya que se ajusta autom�ticamente al borrar elementos del vector
        }
    }
}

