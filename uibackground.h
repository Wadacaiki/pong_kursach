#pragma once
#include "uielement.h"
#include <SFML/Graphics.hpp>

class UIBackground : public UIElement {
public:
    UIBackground(const sf::Texture& texture); // Один конструктор только с текстурой
    void handleEvent(const sf::Event& event) override {}
    void update() override {}
    void draw(sf::RenderWindow& window) override;
    void setTexture(const sf::Texture& newTexture);

private:
    sf::Sprite sprite;
};