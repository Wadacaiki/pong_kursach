#pragma once
#include "uiscreen.h"
#include "uibutton.h"
#include "uitextinput.h"
#include "uibackground.h"
#include <fstream>
#include <set>

class LoginScreen : public UIScreen {
    UITextInput* input;
    UIButton* continueBtn;
    sf::Text message;
    sf::Font font;
    std::string playerName;
    bool nameChecked = false;

public:
    LoginScreen(sf::Font& sharedFont, const sf::Texture& background);
    std::string getPlayerName() const { return playerName; }
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
    bool isNameChecked() const;
};