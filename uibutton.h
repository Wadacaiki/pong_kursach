#pragma once
#include "uielement.h"
#include <functional>

class UIButton : public UIElement {
public:
    UIButton(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::String& label,
        const sf::Font& font, std::function<void()> callback);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
    void setTextColor(sf::Color color);

private:
    sf::RectangleShape shape;
    sf::Text text;
    std::function<void()> onClick;
    bool isHovered = false;
};

