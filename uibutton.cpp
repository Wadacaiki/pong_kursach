#include "uibutton.h"

UIButton::UIButton(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::String& label,
    const sf::Font& font, std::function<void()> callback) : onClick(callback) {
    // Настройка кнопки (прямоугольник)
    shape.setPosition(pos);
    shape.setSize(size);
    shape.setFillColor(sf::Color(200, 200, 200)); // Светло-серый по умолчанию
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);

    // Настройка текста
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    // Центрирование текста по кнопке
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text.setPosition(pos + size / 2.f);
}

void UIButton::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
        isHovered = shape.getGlobalBounds().contains(mousePos);
    }
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (shape.getGlobalBounds().contains(mousePos)) {
            if (onClick) onClick();
        }
    }
}

void UIButton::update() {
    // Обновляем цвет в зависимости от состояния наведения
    if (isHovered) {
        shape.setFillColor(sf::Color(170, 170, 255)); // голубой при наведении
    }
    else {
        shape.setFillColor(sf::Color(200, 200, 200)); // светло-серый по умолчанию
    }
}

void UIButton::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

void UIButton::setTextColor(sf::Color color) {
    text.setFillColor(color);
}