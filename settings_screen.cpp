#include "settings_screen.h"
#include "settings.h"
#include "game.h"
#include <iostream> // Добавляем для std::cerr

SettingsScreen::SettingsScreen(sf::Font& font, const sf::Texture& backgroundTexture, TextureManager* textureManager, Game* game)
    : game(game), textureManager(textureManager) {
    // Фон
    background = new UIBackground(backgroundTexture);
    addElement(background);

    // Кнопка "Тёмная тема"
    darkThemeButton = new UIButton(
        START_BUTTON_POS, MENU_BUTTON_SIZE, L"Тёмная тема", font,
        [this, game, textureManager]() {
            game->setTheme(Theme::Dark, textureManager);
            updateButtonColors();
        }
    );
    addElement(darkThemeButton);

    // Кнопка "Светлая тема"
    lightThemeButton = new UIButton(
        SETTINGS_BUTTON_POS, MENU_BUTTON_SIZE, L"Светлая тема", font,
        [this, game, textureManager]() {
            game->setTheme(Theme::Light, textureManager);
            updateButtonColors();
        }
    );
    addElement(lightThemeButton);

    // Кнопка "Назад"
    UIButton* backButton = new UIButton(
        RECORDS_BUTTON_POS, MENU_BUTTON_SIZE, L"Назад", font,
        [this, game]() { game->switchToMainMenu(); }
    );
    addElement(backButton);

    // Устанавливаем начальные цвета кнопок
    updateButtonColors();
}

void SettingsScreen::updateBackground(const sf::Texture& newBackground) {
    background->setTexture(newBackground); // Заменяем updateTexture на setTexture
}

void SettingsScreen::updateButtonColors() {
    Theme currentTheme = game->getTheme();
    if (currentTheme == Theme::Dark) {
        darkThemeButton->setTextColor(sf::Color::White);
        lightThemeButton->setTextColor(sf::Color(128, 128, 128));
    }
    else {
        darkThemeButton->setTextColor(sf::Color(128, 128, 128));
        lightThemeButton->setTextColor(sf::Color::Black);
    }
}

void SettingsScreen::handleEvent(const sf::Event& event) {
    UIScreen::handleEvent(event);
}

void SettingsScreen::update() {
    UIScreen::update();
}

void SettingsScreen::draw(sf::RenderWindow& window) {
    UIScreen::draw(window);
}