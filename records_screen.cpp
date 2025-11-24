#include "records_screen.h"
#include "game.h"
#include <fstream>
#include <sstream>
#include <algorithm> // Для сортировки
#include <windows.h>
#include <iostream>

RecordsScreen::RecordsScreen(sf::Font& font, const sf::Texture& backgroundTexture, Game* game)
    : game(game), font(font) {
    // Фон
    UIBackground* background = new UIBackground(backgroundTexture);
    addElement(background);

    // Получаем рекорды из Game
    records = game->getRecords();

    // Формируем текст для отображения
    std::stringstream ss;
    ss << u8"Таблица рекордов:\n\n";
    if (records.empty()) {
        ss << u8"Пока нет рекордов\n";
    }
    else {
        for (const auto& [name, score] : records) {
            ss << name << ": " << score << "\n";
        }
    }
    // Сохраняем строку в переменную
    std::string recordStr = ss.str();

    // Преобразуем UTF-8 в UTF-16 (std::wstring)
    int wideSize = MultiByteToWideChar(CP_UTF8, 0, recordStr.c_str(), -1, nullptr, 0);
    std::wstring wideStr(wideSize, 0);
    MultiByteToWideChar(CP_UTF8, 0, recordStr.c_str(), -1, &wideStr[0], wideSize);

    recordsText.setFont(font);
    recordsText.setString(sf::String(wideStr));
    recordsText.setCharacterSize(24);
    recordsText.setFillColor(game->getTheme() == Theme::Dark ? sf::Color::White : sf::Color::Black);
    recordsText.setPosition(SCREEN_WIDTH / 2 - 200, 50);

    // Кнопка "Назад"
    backButton = new UIButton(
        RECORDS_SCREEN_BACK_BUTTON_POS, MENU_BUTTON_SIZE, L"Назад", font,
        [this, game]() { game->switchToMainMenu(); }
    );
    addElement(backButton);
}

void RecordsScreen::handleEvent(const sf::Event& event) {
    UIScreen::handleEvent(event);
}

void RecordsScreen::update() {
    UIScreen::update();
}

void RecordsScreen::draw(sf::RenderWindow& window) {
    UIScreen::draw(window);
    window.draw(recordsText);
}