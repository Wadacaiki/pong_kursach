#include "game_difficulty_screen.h"
#include "settings.h"
#include <iostream>

GameDifficultyScreen::GameDifficultyScreen(sf::Font& font, const sf::Texture& backgroundTexture, Game* game)
    : game(game) {
    // Фон
    UIBackground* background = new UIBackground(backgroundTexture);
    addElement(background);

    // Кнопка "Лёгкий уровень"
    UIButton* easyButton = new UIButton(
        EASY_LEVEL_BUTTON_POS, MENU_BUTTON_SIZE, EASY_LEVEL_BUTTON_TEXT, font,
        [this, game]() {
            std::cerr << u8"Выбран лёгкий уровень\n";
            game->setBallSpeed(3.f, -3.f);
            game->switchToGame();
        }
    );
    addElement(easyButton);

    // Кнопка "Средний уровень"
    UIButton* mediumButton = new UIButton(
        MEDIUM_LEVEL_BUTTON_POS, MENU_BUTTON_SIZE, MEDIUM_LEVEL_BUTTON_TEXT, font,
        [this, game]() {
            std::cerr << u8"Выбран средний уровень\n";
            game->setBallSpeed(5.f, -5.f);
            game->switchToGame();
        }
    );
    addElement(mediumButton);

    // Кнопка "Тяжёлый уровень"
    UIButton* hardButton = new UIButton(
        HARD_LEVEL_BUTTON_POS, MENU_BUTTON_SIZE, HARD_LEVEL_BUTTON_TEXT, font,
        [this, game]() {
            std::cerr << u8"Выбран тяжёлый уровень\n";
            game->setBallSpeed(7.f, -7.f);
            game->switchToGame();
        }
    );
    addElement(hardButton);
}

void GameDifficultyScreen::handleEvent(const sf::Event& event) {
    UIScreen::handleEvent(event);
}

void GameDifficultyScreen::update() {
    UIScreen::update();
}

void GameDifficultyScreen::draw(sf::RenderWindow& window) {
    UIScreen::draw(window);
}