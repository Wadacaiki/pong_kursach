#include "login_screen.h"
#include "settings.h"
#include <iostream>

LoginScreen::LoginScreen(sf::Font& sharedFont, const sf::Texture& background) {
    UIBackground* backgroundElem = new UIBackground(background);
    addElement(backgroundElem);

    font = sharedFont;
    input = new UITextInput({ 200, 250 }, { 400, 50 }, font);
    elements.push_back(input);

    continueBtn = new UIButton(
        { 300, 350 }, { 200, 50 }, CONTINUE_BUTTON_TEXT, font,
        [this]() {
            playerName = input->getText();
            std::cerr << u8"Введённое имя: " << playerName << "\n";
            if (playerName.empty()) {
                std::cerr << u8"Имя пустое, не продолжаем\n";
                return;
            }

            std::ifstream file("players.txt");
            std::set<std::string> names;
            std::string line;
            while (std::getline(file, line)) {
                names.insert(line);
            }
            file.close();

            if (names.count(playerName) == 0) {
                std::ofstream out("players.txt", std::ios::app);
                out << playerName << "\n";
                out.close();
                message.setString(WELCOME_MESSAGE + playerName);
            }
            else {
                message.setString(ENTER_MESSAGE + playerName);
            }

            message.setPosition(200, 150);
            message.setCharacterSize(28);
            message.setFont(font);
            message.setFillColor(sf::Color::Black);

            nameChecked = true;
            std::cerr << u8"Установлено nameChecked = true\n";
        }
    );
    elements.push_back(continueBtn);

    message.setFont(font);
    message.setCharacterSize(28);
    message.setFillColor(sf::Color::Black);
}

void LoginScreen::handleEvent(const sf::Event& event) {
    UIScreen::handleEvent(event);
}

void LoginScreen::update() {
    UIScreen::update();
}

void LoginScreen::draw(sf::RenderWindow& window) {
    UIScreen::draw(window);
    if (nameChecked) {
        window.draw(message);
    }
}

bool LoginScreen::isNameChecked() const {
    return nameChecked;
}
