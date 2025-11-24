#pragma once

#include "uiscreen.h"
#include "uibutton.h"
#include "uibackground.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include "settings.h"

class WelcomeScreen : public UIScreen {
    sf::Text welcomeText;
    UIButton* continueButton;
    std::function<void()> onContinue;

public:
    WelcomeScreen(const sf::Font& font, const sf::Texture& background, const sf::String& playerName, std::function<void()> onContinue);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
};