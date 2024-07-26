#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"

#include <iostream>
#include <vector>
#include <string>

class Enemigo {
protected:

    sf::RectangleShape hitBox;

    sf::Texture texturaGato;
    sf::Sprite spriteGato;


    float anchoSprite;
    float altoSprite;

    float anchoHitbox;
    float altoHitbox;

    float excesoSprite;
    float escalaX;
    float escalaY;

    float velocidadX;
    float velocidadY;

    int velocidadSprite; // a menor es el valor -> mas rapido es el sprite

    bool jumping;

    bool left;
    bool right;
    bool rebote;
    bool stop;

    float jumpTime;

    bool jumpButtonPressed;


    sf::Vector2f TECHO;
    sf::Vector2f PISO;

    float OBJDER;
    float OBJIZQ;

    bool teclaSuelta;
    bool spacePressed;
    float deltaTime;

    bool verificarMoverseMismaPlataforma;

    sf::Vector2f pisoUnicoPlataforma;
    sf::Vector2f deteccionPiso;

    int yTexture;

    sf::Clock clock2;
    float GRAVITY;
    float JUMP_FORCE;
    float MAX_JUMP_TIME;
    float MASS;
    
    std::string spriteMoverFilename;

public:


    //Enemigo(float, float, float, float, float, float, float, float, int, float, float, float , float);
    Enemigo();

    virtual ~Enemigo() = default;

    bool colisionLados = false;


    virtual void detectarPiso(const std::vector<std::vector<int>>&, sf::Vector2f&);

    virtual void detectarTecho(const std::vector<std::vector<int>>&);

    virtual void detectarObjDer(const std::vector<std::vector<int>>&);

    virtual void detectarObjIzq(const std::vector<std::vector<int>>&);

    virtual void update(float, const std::vector<std::vector<int>>&) = 0;

    virtual void drawTo(sf::RenderWindow&);

    sf::Vector2f getPosition() const;


    void applyGravity();

    void controlarMovimientoVertical();

    virtual void controlarMovimientoHorizontal(float);

    void loadSpriteSheet(const std::string&);

    void moverHorizontalSprite(bool, bool);

    sf::RectangleShape getHitBox();

    float getAnchoHitbox();

    float getAltoHitbox();
    
    float getAnchoSprite();

    float getAltoSprite();

    float getExcesoSprite();

    float getPosX();

    float getPosY();

    std::string getSpriteMoverFilename();

    void parar();

    void detectarOjbIzqDerPlataforma(const std::vector<std::vector<int>> map, int);

    void moverseMismaPlataforma(const std::vector<std::vector<int>>);

    void detectarPisoRoto(const std::vector<std::vector<int>>);

    void setPosicion(float, float);
    void setTamanhoHitbox(float, float);
    void setAnchoHitbox(float);
    void setAltoHitbox(float);
    void setExcesoSprite(float);
    void setAnchoSprite(float);
    void setAltoSprite(float);
    void setEscalaX(float);
    void setEscalaY(float);
    void setVelocidadX(float);
    void setVelocidadSprite(int);
    void setGravedad(float);
    void setFuerzaSalto(float);
    void setMasa(float);
    void setMaxTiempoSalto(float);
    void setSpriteMoverFilename(std::string);

};


#endif // !ENEMIGO