#pragma once
#include <SFML/Graphics.hpp>

class UIElement {
public:
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~UIElement() = default;
};

