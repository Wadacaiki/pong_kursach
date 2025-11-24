#pragma once
#include "settings.h"
#include "SFML/Graphics.hpp"
#include "ball.h"
#include "login_screen.h"
#include "main_menu_screen.h"
#include "welcome_screen.h"
#include "texture_manager.h"
#include "platforma.h"
#include "text_obj.h"

// Предварительные объявления
class GameDifficultyScreen;
class MainMenuScreen;
class SettingsScreen;
class RecordsScreen; // Добавляем

class Game {
public:
    Game();
    ~Game();
    void play();

    enum class GameState { Login, Welcome, MainMenu, ChooseDifficulty, Settings, MainGame, Records, GameOver };
    void setBallSpeed(float speedx, float speedy);
    void switchToGame();
    void setTheme(Theme newTheme, TextureManager* textureManager = nullptr);
    Theme getTheme() const { return currentTheme; }
    void switchToChooseDifficulty();
    void switchToSettings();
    void switchToMainMenu();
    void switchToRecords();
    void saveScore();
    std::string getPlayerName() const { return playerName; }
    const std::vector<std::pair<std::string, int>>& getRecords() const { return records; }

private:
    sf::RenderWindow* window;
    Ball* ball;
    sf::Font font;
    GameState state;
    TextureManager textureManager;
    Platforma* platforma;
    int score;
    TextObject* score_text;
    std::string playerName; // Для хранения имени игрока

    UIScreen* currentScreen;
    LoginScreen* loginScreen;
    MainMenuScreen* mainMenuScreen;
    GameDifficultyScreen* gameDifficultyScreen;
    WelcomeScreen* welcomeScreen;
    Theme currentTheme = Theme::Dark;
    SettingsScreen* settingsScreen;
    RecordsScreen* recordsScreen;
    TextObject* gameOverText; // Для отображения текста конца игры
    sf::Clock gameOverTimer;
    bool recordsLoaded = false;

    void loadTextures();
    void check_events();
    void update();
    void check_collisions();
    void draw();

    void switchToWelcomeScreen();

    void updateScreenTheme();
    void loadTheme();
    void saveTheme();

    std::vector<std::pair<std::string, int>> records; // Добавляем для хранения рекордов
    void loadRecords(); // Новый метод для загрузки рекордов
    void saveRecords(); // Новый метод для сохранения рекордов
};