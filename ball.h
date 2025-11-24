#pragma once
#include "SFML/Graphics.hpp"
#include "settings.h"

class Ball {
public:
    Ball(const sf::Texture& texture);
    void update();
    void bounceVertical();
    void bounceHorizontal();
    void draw(sf::RenderWindow* window);
    sf::FloatRect getHitBox();
    void setSpeed(float speedx, float speedy);
    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    sf::Vector2f getPreviousPosition() const { return previousPos; }
    void setPosition(float x, float y);
    float getSpeedY() const { return speedy; }
    float getSpeedX() const { return speedx; }
    void updateTexture(const sf::Texture& newTexture);
    void reset();
    bool isReset() const { return justReset; } // Новый метод для проверки состояния сброса

private:
    float x = 0.f;
    float y = 0.f;
    float speedx = 5.f;
    float speedy = 5.f;
    sf::Sprite sprite;
    sf::Vector2f previousPos;
    bool justReset = false; // Флаг, чтобы пропустить первый update после reset
};