#include "Mapa.h"
#include "Definitions.hpp"

Mapa::Mapa(const std::string& filename, const std::string& spriteSheet) {
    loadMap(filename);
    loadSpriteSheet(spriteSheet);
}

void Mapa::draw(sf::RenderWindow& window) {
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            int tileValue = map[row][col];
            if ((tileValue > 0 && tileValue < cantBloquesMapaSprite)) { // Enemigo
                sprites[tileValue - 1].setPosition(col * cellSize, row * cellSize);
                window.draw(sprites[tileValue - 1]);
            }
        }
    }
}

const std::vector<std::vector<int>>& Mapa::getMap() const {
    return map;
}
void Mapa::loadMap(const std::string& filename) {
    map.resize(numRows, std::vector<int>(numCols));
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return;
    }

    std::string line;
    int row = 0;
    while (std::getline(file, line) && row < numRows) {
        std::istringstream iss(line);
        for (int col = 0; col < numCols; ++col) {
            iss >> map[row][col];
        }
        ++row;
    }

    file.close();
}

void Mapa::loadSpriteSheet(const std::string& filename) {

    if (!texture.loadFromFile(filename)) {
        std::cerr << "Error al cargar el spritesheet" << std::endl;
        return;
    }

    sprites.resize(cantBloquesMapaSprite);
    for (int i = 0; i < cantBloquesMapaSprite; ++i) {
        sprites[i].setTexture(texture);
        int x = (i % numColumnasSpriteMapa) * cellSize;
        int y = (i / numFilasSpriteMapa) * cellSize;
        sprites[i].setTextureRect(sf::IntRect(x, y, cellSize, cellSize));
    }
}


void Mapa::setValMap(int i, int j, int val) {
	map[i][j] = val;

}

int Mapa::getValMap(int i, int j) const {
	return map[i][j];
}