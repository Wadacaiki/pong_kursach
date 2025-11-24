#pragma once
#include "uiscreen.h"
#include "uibutton.h"
#include "uibackground.h"
#include <SFML/Graphics.hpp>
#include "settings.h"
#include "texture_manager.h"

class Game;

class SettingsScreen : public UIScreen {
public:
    SettingsScreen(sf::Font& font, const sf::Texture& backgroundTexture, TextureManager* textureManager, Game* game);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
    void updateBackground(const sf::Texture& newBackground);

private:
    Game* game;
    TextureManager* textureManager;
    UIBackground* background;
    UIButton* darkThemeButton; // Для доступа к кнопке
    UIButton* lightThemeButton; // Для доступа к кнопке
    void updateButtonColors(); // Для обновления цвета кнопок
};