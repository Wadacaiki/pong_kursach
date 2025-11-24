#include "platforma.h"

Platforma::Platforma(const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(SCREEN_WIDTH / 2.5, SCREEN_HEIGHT - 100);
}

void Platforma::update() {
    sf::Vector2f speed(0.f, 0.f);
    const float platformSpeed = 5.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        speed.x = -platformSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        speed.x = platformSpeed;
    }

    sprite.move(speed);
    sf::Vector2f curr_pos = sprite.getPosition();
    if (curr_pos.x <= 0) {
        curr_pos.x = 0;
    }
    if (curr_pos.x >= SCREEN_WIDTH - getHitBox().width) {
        curr_pos.x = SCREEN_WIDTH - getHitBox().width;
    }

    sprite.setPosition(curr_pos);
}

void Platforma::draw(sf::RenderWindow* window) {
    window->draw(sprite);
}

sf::FloatRect Platforma::getHitBox() {
    return sprite.getGlobalBounds();
}

void Platforma::updateTexture(const sf::Texture& newTexture) {
    sprite.setTexture(newTexture);
}

void Platforma::reset() {
    sprite.setPosition(SCREEN_WIDTH / 2.f - sprite.getGlobalBounds().width / 2.f, SCREEN_HEIGHT - 100.f); // Начальная позиция
}