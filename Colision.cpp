#include "Colision.h"

void Colision::verificarColisionHitbox(Gato* gato, std::vector<Enemigo*>& enemigos) {
    for (size_t i = 0; i < enemigos.size(); i++) {
        if(!enemigos[i]->getHitBox().getGlobalBounds().intersects(gato->getHitBox().getGlobalBounds())) {
    
            // Colision por arriba-abajo
            if (
                enemigos[i]->getPosX() + enemigos[i]->getAltoHitbox() + 1.0f > gato->getPosX() &&
                enemigos[i]->getPosX() < gato->getPosX()  + gato->getAnchoHitbox() + 1.0f
                ) {
                enemigos[i]->colisionLados = false;
            }

            // Colision por los lados
            if (
                enemigos[i]->getPosY() < gato->getPosY() + gato->getAltoHitbox() + 1.0f &&
                enemigos[i]->getPosY() + enemigos[i]->getAltoHitbox() + 1.0f > gato->getPosY()
                ) {
                enemigos[i]->colisionLados = true;
            }            
        }
        else {
		
		    if (enemigos[i]->colisionLados) { // player colisiona en los lados -> player muere
                //gato->parar();
				gato->morir();  
            }
		    else { // player colisiona arriba o abajo -> enemigo muere
                //enemigos[i]->parar();
                delete enemigos[i];
				enemigos.erase(enemigos.begin() + i);
            }
        }
    }
}