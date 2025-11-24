#include "text_obj.h"

TextObject::TextObject(sf::Font& font, int size, float x, float y, sf::Color color) {
    this->font = font;
    text.setFont(font);
    text.setCharacterSize(size);
    text.setPosition(x, y);
    text.setFillColor(color);
}

void TextObject::update(std::string str) {
    text.setString(str);
}

void TextObject::update(std::wstring wstr) {
    text.setString(sf::String(wstr));
}

void TextObject::draw(sf::RenderWindow* window) {
    window->draw(text);
}

void TextObject::setColor(sf::Color newColor) {
    text.setFillColor(newColor);
}

void TextObject::centerHorizontally(float screenWidth) {
    sf::FloatRect textBounds = text.getGlobalBounds();
    float x = (screenWidth - textBounds.width) / 2;
    text.setPosition(x, text.getPosition().y);
}

void TextObject::centerVertically(float screenHeight) {
    sf::FloatRect textBounds = text.getGlobalBounds();
    float y = (screenHeight - textBounds.height) / 2;
    text.setPosition(text.getPosition().x, y);
}