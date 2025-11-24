#include "ball.h"
#include <iostream>

Ball::Ball(const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    x = SCREEN_WIDTH / 2.f;
    y = SCREEN_HEIGHT / 2.f;
    previousPos = sprite.getPosition();
}

void Ball::update() {
    if (justReset) {
        justReset = false; // Пропускаем первый кадр после сброса
        std::cerr << u8"Ball update skipped after reset: pos=" << x << "," << y << "\n";
        return;
    }

    previousPos = sprite.getPosition();
    x += speedx;
    y += speedy;
    sprite.setPosition(x, y);
    sf::Vector2f pos = sprite.getPosition();
    if (pos.x > SCREEN_WIDTH - getHitBox().width || pos.x < 0) {
        speedx = -speedx;
    }
    if (pos.y < 0) {
        speedy = -speedy;
    }
    std::cerr << u8"Ball update: pos=" << x << "," << y << ", speed=" << speedx << "," << speedy << "\n";
}

void Ball::bounceVertical() {
    speedy = -speedy;
}

void Ball::bounceHorizontal() {
    speedx = -speedx;
}

void Ball::draw(sf::RenderWindow* window) {
    window->draw(sprite);
}

sf::FloatRect Ball::getHitBox() {
    sf::FloatRect hitBox = sprite.getGlobalBounds();
    return hitBox;
}

void Ball::setSpeed(float speedx, float speedy) {
    this->speedx = speedx;
    this->speedy = speedy;
    std::cerr << u8"Ball speed set: " << speedx << "," << speedy << "\n";
}

void Ball::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    sprite.setPosition(x, y);
    previousPos = sprite.getPosition();
}

void Ball::updateTexture(const sf::Texture& newTexture) {
    sprite.setTexture(newTexture);
}

void Ball::reset() {
    x = SCREEN_WIDTH / 2.f;
    y = SCREEN_HEIGHT / 2.f;
    sprite.setPosition(x, y);
    previousPos = sprite.getPosition();
    justReset = true; // Устанавливаем флаг сброса
    std::cerr << u8"Ball reset: pos=" << x << "," << y << "\n";
}