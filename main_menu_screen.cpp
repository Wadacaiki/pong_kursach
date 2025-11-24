#include "settings.h"
#include "main_menu_screen.h"
#include "game.h" // Добавляем, так как используем методы Game

MainMenuScreen::MainMenuScreen(sf::Font& font, TextureManager* textureManager, Game* game)
    : font(font), textureManager(textureManager), game(game) {
    // Фон
    Theme theme = game->getTheme(); // Получаем текущую тему
    std::string key = (theme == Theme::Dark) ? TEXTURE_SCREEN_DARK_BG_KEY : TEXTURE_SCREEN_LIGHT_BG_KEY;
    UIBackground* background = new UIBackground(textureManager->getTexture(key));
    addElement(background);

    // Кнопка "Начать игру"
    startButton = new UIButton(START_BUTTON_POS, MENU_BUTTON_SIZE, START_BUTTON_TEXT, font, [this, game]() {
        game->switchToChooseDifficulty();
        });
    addElement(startButton);

    // Кнопка "Настройки"
    settingsButton = new UIButton(SETTINGS_BUTTON_POS, MENU_BUTTON_SIZE, SETTINGS_BUTTON_TEXT, font, [this, game]() {
        game->switchToSettings();
        });
    addElement(settingsButton);

    // Кнопка "Таблица рекордов"
    recordsButton = new UIButton(RECORDS_BUTTON_POS, MENU_BUTTON_SIZE, RECORDS_BUTTON_TEXT, font, [this, game]() {
        game->switchToRecords();
        });

    addElement(recordsButton);

    // Кнопка "Выход"
    exitButton = new UIButton(EXIT_BUTTON_POS, MENU_BUTTON_SIZE, EXIT_BUTTON_TEXT, font, []() {
        exit(0);
        });
    addElement(exitButton);
}

void MainMenuScreen::handleEvent(const sf::Event& event) {
    UIScreen::handleEvent(event);
}

void MainMenuScreen::update() {
    UIScreen::update();
}

void MainMenuScreen::draw(sf::RenderWindow& window) {
    UIScreen::draw(window);
}
