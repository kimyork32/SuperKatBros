
#pragma once
#include <SFML/Graphics.hpp>
#include "Definitions.hpp"

const float GRAVITY = 3000.0f;
const float JUMP_FORCE = -5000.0f;
const float MAX_JUMP_TIME = 1.0f;
const float MASS = 5.00f;

class Entity {
private:
    bool jumping = false;
    sf::RectangleShape rect;
    float tamPersonaje;

    bool left;
    bool right;

    float speed;
    float velocityY;
    float jumpTime;

    bool jumpButtonPressed;
    bool rebot;

    float TECHO;
    float GROUND_LEVEL;

public:
    bool teclaSuelta;
    bool spacePressed;
    sf::Clock clock2;

    Entity(float x, float y, float size) {
        this->tamPersonaje = size;
        rect.setPosition(x, y);
        rect.setSize(sf::Vector2f(size, size));
        rect.setFillColor(sf::Color::Red);
        speed = 320.0f;
        left = false;
        right = false;

        spacePressed = false;
        jumpButtonPressed = false;
        rebot = false;
        teclaSuelta = false;

        velocityY = 0.0f;
        jumpTime = 0.0f;
        TECHO = 0.0f;
        GROUND_LEVEL = 0.0f;
    }

    void processEvents(sf::Keyboard::Key key, bool checkPressed) {
        if (checkPressed) {
            if (key == sf::Keyboard::Left)
                left = true;
            if (key == sf::Keyboard::Right)
                right = true;
        }
        else {
            if (key == sf::Keyboard::Left)
                left = false;
            if (key == sf::Keyboard::Right)
                right = false;
        }
    }
    
    void jump() {
        
        if (rect.getPosition().y+1 >= GROUND_LEVEL - tamPersonaje) {
            velocityY = JUMP_FORCE / MASS;
            jumpTime = 0.0f;

        }
    }


    void update(float deltaTime, const std::vector<std::vector<int>>& map, int cellSize) {
        jumpButtonPressed = static_cast<bool>(spacePressed && clock2.getElapsedTime().asMilliseconds() < 800 && !rebot && !teclaSuelta);
        

        if ((rect.getPosition().y >= 0 && rect.getPosition().y + tamPersonaje < numRows * cellSize) && (rect.getPosition().x >= 0 && rect.getPosition().x + tamPersonaje < numCols*cellSize )) { 
            for (int i = rect.getPosition().y / cellSize; i < numRows; i++) {
                if (map[i][rect.getPosition().x / cellSize] != 0 || map[i][(rect.getPosition().x + rect.getSize().x) / cellSize] != 0) {
                    GROUND_LEVEL = i * cellSize;
                    break;
                }
                else {
                    GROUND_LEVEL = 400.0f;
                }
            }

            for (int i = rect.getPosition().y / cellSize; i >= 0; i--) {
                if (map[i][rect.getPosition().x / cellSize] != 0 || map[i][(rect.getPosition().x + rect.getSize().x) / cellSize] != 0) {
                    TECHO = i * cellSize;
                    break;
                }
                else {
                    TECHO = -1000.0f;
                }
            }
        }

        if (rect.getPosition().y >= GROUND_LEVEL - tamPersonaje - 1.0f) {
            rebot = false;
        }

        
        if (jumpButtonPressed) {
            jump();
            jumpTime += deltaTime;
			velocityY += (JUMP_FORCE / MASS) * deltaTime / MAX_JUMP_TIME;
        }

        velocityY += GRAVITY * deltaTime;
		
        float nextMove = rect.getPosition().y + velocityY * deltaTime;

        if (nextMove <= TECHO + cellSize + 1.0f) {
            nextMove = TECHO + cellSize + 1.0f;
            velocityY = 0;
            rebot = true;
            teclaSuelta = true;
        }

        rect.move(0.f, nextMove - rect.getPosition().y);

        if (rect.getPosition().y >= GROUND_LEVEL - tamPersonaje - 1.0f) {
            rect.setPosition(rect.getPosition().x, GROUND_LEVEL - tamPersonaje - 1.0f);
            velocityY = 0.0f;
        }

        sf::Vector2f movement(0.f, 0.f);                                                                                        

        if (left)
            movement.x -= speed * deltaTime;
        if (right)
            movement.x += speed * deltaTime;

        sf::Vector2f newPosition = rect.getPosition() + movement;

        
        if (movement.x != 0) {
            sf::Vector2f horizontalPosition = rect.getPosition() + sf::Vector2f(movement.x, 0.f);
            int leftCell = static_cast<int>(horizontalPosition.x / cellSize);
            int rightCell = static_cast<int>((horizontalPosition.x + rect.getSize().x) / cellSize);
            int topCell = static_cast<int>(horizontalPosition.y / cellSize);
            int bottomCell = static_cast<int>((horizontalPosition.y + rect.getSize().y) / cellSize);

            bool collision = false;
            if ((rect.getPosition().y >= 0 && rect.getPosition().y + tamPersonaje < numRows * cellSize) && (rect.getPosition().x >= 0 && rect.getPosition().x + tamPersonaje < numCols * cellSize)) {
                if (map[topCell][leftCell] != 0 || map[topCell][rightCell] != 0 ||
                    map[bottomCell][leftCell] != 0 || map[bottomCell][rightCell] != 0) {
                    collision = true;
                }
            }

            if (!collision) {
                rect.move(movement.x, 0.f);
            }
        }
        
        
    }

    void drawTo(sf::RenderWindow& window) {
        window.draw(rect);
    }

    sf::Vector2f getPosition() const {
        return rect.getPosition();
    }
};
