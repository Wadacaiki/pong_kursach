#pragma once
#include <string>
#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const std::string TITLE = "Pong";
const std::string FONT_FILE_NAME = "TDAText.ttf";
const sf::String WELCOME_MESSAGE = L"Добро пожаловать, ";
const sf::String ENTER_MESSAGE = L"Привет, ";
const sf::String CONTINUE_BUTTON_TEXT = L"Далее";
const sf::String START_BUTTON_TEXT = L"Начать игру";
const sf::String SETTINGS_BUTTON_TEXT = L"Настройки";
const sf::String RECORDS_BUTTON_TEXT = L"Таблица рекордов";
const sf::String EXIT_BUTTON_TEXT = L"Выход";
const sf::Vector2f MENU_BUTTON_SIZE = { 300.f, 50.f };
const sf::Vector2f START_BUTTON_POS = { 250.f, 200.f };
const sf::Vector2f SETTINGS_BUTTON_POS = { 250.f, 270.f };
const sf::Vector2f RECORDS_BUTTON_POS = { 250.f, 340.f };
const sf::Vector2f EXIT_BUTTON_POS = { 250.f, 410.f };
const std::string PLAYER_DATA_FILE = "player.txt";
const sf::Vector2f CONTINUE_BUTTON_POS = { 250.f, 400.f };
const sf::Vector2f RECORDS_SCREEN_BACK_BUTTON_POS = { 250.f, 500.f };
// Кнопки экрана выбора сложности игры
const sf::Vector2f EASY_LEVEL_BUTTON_POS = { 250.f, 270.f };
const sf::Vector2f MEDIUM_LEVEL_BUTTON_POS = { 250.f, 340.f };
const sf::Vector2f HARD_LEVEL_BUTTON_POS = { 250.f, 410.f };
const sf::String EASY_LEVEL_BUTTON_TEXT = L"Лёгкий";
const sf::String MEDIUM_LEVEL_BUTTON_TEXT = L"Средний";
const sf::String HARD_LEVEL_BUTTON_TEXT = L"Тяжёлый";
// Пути к файлам
const std::string TEXTURE_DARK_BALL_FILE = "dark_ball.png"; // Добавляем для тёмной темы
const std::string TEXTURE_LIGHT_BALL_FILE = "light_ball.png"; // Добавляем для светлой темы
const std::string TEXTURE_DARK_PLATFORM_FILE = "dark_platform.png"; // Добавляем
const std::string TEXTURE_DARK_PLATFORM_KEY = "dark_platform"; // Добавляем
const std::string TEXTURE_LIGHT_PLATFORM_FILE = "light_platform.png"; // Добавляем
const std::string TEXTURE_LIGHT_PLATFORM_KEY = "light_platform"; // Добавляем
// Ключи для менеджера текстур
const std::string TEXTURE_LIGHT_BALL_KEY = "light_ball"; // Ключ для светлой текстуры
const std::string TEXTURE_DARK_BALL_KEY = "dark_ball"; // Ключ для тёмной текстуры
// Фоны экранов uiscreen
enum class Theme { Dark, Light };
const std::string TEXTURE_SCREEN_LIGHT_BG_FILE = "light_bg.jpg";
const std::string TEXTURE_SCREEN_LIGHT_BG_KEY = "screen_bg_light";
const std::string TEXTURE_SCREEN_DARK_BG_FILE = "dark_bg.jpg";
const std::string TEXTURE_SCREEN_DARK_BG_KEY = "screen_bg_dark";

//const std::string TEXTURE_BUTTON_KEY = "button";