#pragma once
#include <SFML/Graphics.hpp>

class TextObject {
private:
    sf::Text text;
    sf::Font font;

public:
    TextObject(sf::Font& font, int size, float x, float y, sf::Color color);
    void update(std::string str);
    void update(std::wstring wstr);
    void draw(sf::RenderWindow* window);
    void setColor(sf::Color newColor);
    void centerHorizontally(float screenWidth);
    void centerVertically(float screenHeight);
};