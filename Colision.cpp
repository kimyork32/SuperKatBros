#include "Colision.h"

// colision con enemigos
void Colision::verificarColisionHitboxEnemigo(std::unique_ptr<Gato>& gato, std::vector<std::unique_ptr<Enemigo>>& enemigos) {
    for (size_t i = 0; i < enemigos.size(); /* no incrementar i aquí */) {
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
            // No incrementar i aquí, ya que se ajusta automáticamente al borrar elementos del vector
        }
    }
}


void Colision::verificarColisionHitboxItem(std::unique_ptr<Gato>& gato, std::vector<std::shared_ptr<Item>>& items) {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i]->getHitBox().getGlobalBounds().intersects(gato->getHitBox().getGlobalBounds()))  {
            if (auto moneda = std::dynamic_pointer_cast<Moneda>(items[i])) {
                gato->aumentarMonedas();
                items.erase(items.begin() + i);
            }
            else if (auto catnip = std::dynamic_pointer_cast<Catnip>(items[i])) {
                gato->aumentarVelocidadX(catnip->getVelocidadX());
                items.erase(items.begin() + i);
            }
        }
        
        else {
            ++i; 
        }
    }
}


void Colision::verificarColisionBalaEnemigo(std::unique_ptr<Gato>& gato, std::vector<std::unique_ptr<Enemigo>>& enemigos) {
    for (int i = 0; i < enemigos.size();) {
        if (gato->verificarColisionBalaEnemigo(enemigos[i])) {
            enemigos.erase(enemigos.begin() + i);
        }
        ++i;
    }
}
