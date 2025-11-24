#include "welcome_screen.h"
#include "settings.h"
#include <fstream>

WelcomeScreen::WelcomeScreen(const sf::Font& font, const sf::Texture& background,
    const sf::String& playerName, std::function<void()> onContinue) : onContinue(onContinue) {
    // Фон
    UIBackground* bg = new UIBackground(background);
    addElement(bg);

    // Проверка: новый ли игрок
    bool isReturning = false;
    std::wifstream in(PLAYER_DATA_FILE);
    in.imbue(std::locale("")); // Включаем поддержку Unicode

    std::wstring rawLine;
    while (std::getline(in, rawLine)) {
        sf::String line = rawLine;
        if (line == playerName) {
            isReturning = true;
            break;
        }
    }
    in.close();

    // Если новый — добавить в файл
    if (!isReturning) {
        std::wofstream out(PLAYER_DATA_FILE, std::ios::app);
        out.imbue(std::locale(""));
        out << playerName.toWideString() << L"\n";
        out.close();
    }

    // Сообщение
    sf::String message = isReturning ? ENTER_MESSAGE + playerName + L"!" : WELCOME_MESSAGE + playerName + L"!";
    welcomeText.setFont(font);
    welcomeText.setString(message);
    welcomeText.setCharacterSize(32);
    welcomeText.setFillColor(sf::Color::White);
    // Центрирование по горизонтали
    sf::FloatRect textBounds = welcomeText.getLocalBounds();
    welcomeText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top);
    welcomeText.setPosition(SCREEN_WIDTH / 2.f, 200.f);

    // Кнопка "Далее"
    continueButton = new UIButton(
        CONTINUE_BUTTON_POS,
        MENU_BUTTON_SIZE,
        CONTINUE_BUTTON_TEXT,
        font,
        this->onContinue
    );
    addElement(continueButton);
}

void WelcomeScreen::handleEvent(const sf::Event& event) {
    UIScreen::handleEvent(event);
}

void WelcomeScreen::update() {
    UIScreen::update();
}

void WelcomeScreen::draw(sf::RenderWindow& window) {
    UIScreen::draw(window);
    window.draw(welcomeText);
}