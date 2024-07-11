#include "BloqueDestruible.h"

BloqueDestruible::BloqueDestruible(float x, float y) : Bloque(x, y) {
	hitBox.setFillColor(sf::Color::Magenta);
}
