#include "uibackground.h"

UIBackground::UIBackground(const sf::Texture& texture) {
    sprite.setTexture(texture);
}

void UIBackground::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void UIBackground::setTexture(const sf::Texture& newTexture) {
    sprite.setTexture(newTexture);
}