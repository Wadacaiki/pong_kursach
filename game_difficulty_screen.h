#pragma once
#include "uiscreen.h"
#include "uibutton.h"
#include "uibackground.h"
#include <SFML/Graphics.hpp>
#include "game.h"

class GameDifficultyScreen : public UIScreen {
public:
    GameDifficultyScreen(sf::Font& font, const sf::Texture& backgroundTexture, Game* game);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;

private:
    Game* game; // ”казатель на Game дл€ вызова методов
};