#pragma once
#include "uiscreen.h"
#include "uibutton.h"
#include "uibackground.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "settings.h"

// Предварительное объявление
class Game;

class RecordsScreen : public UIScreen {
public:
    RecordsScreen(sf::Font& font, const sf::Texture& backgroundTexture, Game* game);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;

private:
    Game* game;
    sf::Font font;
    sf::Text recordsText; // Текст для отображения рекордов
    std::vector<std::pair<std::string, int>> records; // Список рекордов
    UIButton* backButton;
};
