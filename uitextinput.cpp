#include "UITextInput.h"
#include <iostream>

UITextInput::UITextInput(const sf::Vector2f& pos, const sf::Vector2f& size, sf::Font& font) {
    box.setPosition(pos);
    box.setSize(size);
    box.setFillColor(sf::Color::White);
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::Black);

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(pos.x + 5, pos.y + 5);
}

std::string UITextInput::getText() const {
    return content;
}

void UITextInput::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        // Фокус по клику
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        isFocused = box.getGlobalBounds().contains(mousePos);
    }

    if (!isFocused) return;

    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 32 && event.text.unicode < 127) {
            content.insert(cursorPos, 1, static_cast<char>(event.text.unicode));
            cursorPos++;
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Left:
            if (cursorPos > 0) cursorPos--;
            break;
        case sf::Keyboard::Right:
            if (cursorPos < content.size()) cursorPos++;
            break;
        case sf::Keyboard::Backspace:
            if (cursorPos > 0) {
                content.erase(cursorPos - 1, 1);
                cursorPos--;
            }
            break;
        case sf::Keyboard::Delete:
            if (cursorPos < content.size()) {
                content.erase(cursorPos, 1);
            }
            break;
        default:
            break;
        }
    }
}

void UITextInput::update() {
    // Мигающий курсор
    if (cursorTimer.getElapsedTime().asSeconds() > 0.5f) {
        showCursor = !showCursor;
        cursorTimer.restart();
    }

    // Обновление отрисовываемого текста
    text.setString(content);
}

void UITextInput::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);

    if (isFocused && showCursor) {
        // Расчёт позиции курсора
        std::string substr = content.substr(0, cursorPos);
        sf::Text cursorText(sf::String(substr), *text.getFont(), text.getCharacterSize());
        cursorText.setCharacterSize(text.getCharacterSize());
        cursorText.setPosition(text.getPosition());

        float cursorX = text.getPosition().x + cursorText.getLocalBounds().width;
        float cursorY = text.getPosition().y;

        sf::RectangleShape cursor(sf::Vector2f(2, text.getCharacterSize()));
        cursor.setFillColor(sf::Color::Black);
        cursor.setPosition(cursorX, cursorY);

        window.draw(cursor);
    }
}
