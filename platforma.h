#pragma once
#include "SFML/Graphics.hpp"
#include "settings.h"

class Platforma {
public:
    Platforma(const sf::Texture& texture);
    void update();
    void draw(sf::RenderWindow* window);
    sf::FloatRect getHitBox();
    void updateTexture(const sf::Texture& newTexture);
    void reset();

private:
    sf::Sprite sprite;
};