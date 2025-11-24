#pragma once
#include "uielement.h"

class UITextInput : public UIElement {
    sf::RectangleShape box;
    sf::Text text;
    std::string content;
    size_t cursorPos = 0;
    bool isFocused = false;
    sf::Clock cursorTimer;
    bool showCursor = true;

public:
    UITextInput(const sf::Vector2f& pos, const sf::Vector2f& size, sf::Font& font);
    std::string getText() const;
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
};
