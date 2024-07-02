#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "Definitions.hpp"
#include "Enemigo.h"

class Mapa {
private:
    std::vector<std::vector<int>> map;
    std::vector<sf::Sprite> sprites;
    sf::Texture texture;


public:
    Mapa(const std::string& filename, const std::string& spriteSheet);

    void draw(sf::RenderWindow& window);

    const std::vector<std::vector<int>>& getMap() const;
    
    void loadMap(const std::string& filename);

    void loadSpriteSheet(const std::string& filename);
    
    //void crearEnemigos(std::vector<Enemigo>& enemigos);

    void setValMap(int, int, int);

	int getValMap(int, int) const;
    
};
