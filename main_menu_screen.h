#pragma once
#include "uiscreen.h"
#include "uibutton.h"
#include "uibackground.h"
#include <SFML/Graphics.hpp>
#include "settings.h" // Для Theme
#include "texture_manager.h" // Для TextureManager

// Предварительное объявление вместо #include
class Game;

class MainMenuScreen : public UIScreen {
protected:
    UIButton* startButton;
    UIButton* settingsButton;
    UIButton* recordsButton;
    UIButton* exitButton;
    sf::Font font;
    Game* game;
    TextureManager* textureManager;

public:
    MainMenuScreen(sf::Font& font, TextureManager* textureManager, Game* game);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
};
