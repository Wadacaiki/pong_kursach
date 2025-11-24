#include "game.h"
#include "game_difficulty_screen.h"
#include <iostream>
#include "settings_screen.h"
#include <windows.h>
#include "records_screen.h"
#include <sstream>

Game::Game() {
    // Устанавливаем кодировку консоли на UTF-8
    SetConsoleOutputCP(CP_UTF8);
    std::cerr.imbue(std::locale(""));
    sf::err().rdbuf(std::cerr.rdbuf());

    window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE);
    window->setVerticalSyncEnabled(true);

    if (!font.loadFromFile(FONT_FILE_NAME)) {
        std::cerr << u8"Ошибка загрузки шрифта\n";
    }

    loadTheme();
    loadTextures();
    loadRecords(); // Загружаем рекорды при запуске

    loginScreen = new LoginScreen(font, textureManager.getTexture(currentTheme == Theme::Dark ? TEXTURE_SCREEN_DARK_BG_KEY : TEXTURE_SCREEN_LIGHT_BG_KEY));
    mainMenuScreen = new MainMenuScreen(font, &textureManager, this);
    currentScreen = loginScreen;
    welcomeScreen = nullptr;
    state = GameState::Login;
    ball = new Ball(textureManager.getTexture(currentTheme == Theme::Dark ? TEXTURE_DARK_BALL_KEY : TEXTURE_LIGHT_BALL_KEY));
    platforma = new Platforma(textureManager.getTexture(currentTheme == Theme::Dark ? TEXTURE_DARK_PLATFORM_KEY : TEXTURE_LIGHT_PLATFORM_KEY));
    score = 0;
    score_text = new TextObject(font, 24, 5, 5, currentTheme == Theme::Dark ? sf::Color::White : sf::Color::Black);
    gameOverText = new TextObject(font, 36, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 50,
        currentTheme == Theme::Dark ? sf::Color::White : sf::Color::Black); // Цвет зависит от темы
}

void Game::loadTextures() {
    std::vector<std::pair<std::string, std::string>> texturesToLoad = {
        {TEXTURE_SCREEN_DARK_BG_KEY, TEXTURE_SCREEN_DARK_BG_FILE},
        {TEXTURE_SCREEN_LIGHT_BG_KEY, TEXTURE_SCREEN_LIGHT_BG_FILE},
        {TEXTURE_DARK_PLATFORM_KEY, TEXTURE_DARK_PLATFORM_FILE},
        {TEXTURE_LIGHT_PLATFORM_KEY, TEXTURE_LIGHT_PLATFORM_FILE},
        {TEXTURE_DARK_BALL_KEY, TEXTURE_DARK_BALL_FILE},
        {TEXTURE_LIGHT_BALL_KEY, TEXTURE_LIGHT_BALL_FILE}
    };

    for (const auto& [key, file] : texturesToLoad) {
        if (!textureManager.loadTexture(key, file)) {
            std::cerr << "Ошибка загрузки: " << file << std::endl;
        }
    }
}

void Game::check_events() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (currentScreen != nullptr) {
            currentScreen->handleEvent(event);
        }
    }
}

void Game::update() {
    if (state == GameState::Login) {
        loginScreen->update();
        if (loginScreen->isNameChecked()) {
            switchToWelcomeScreen();
        }
    }
    else if (state == GameState::Welcome) {
        welcomeScreen->update();
    }
    else if (state == GameState::MainMenu) {
        mainMenuScreen->update();
    }
    else if (state == GameState::ChooseDifficulty) {
        gameDifficultyScreen->update();
    }
    else if (state == GameState::Settings) {
        settingsScreen->update();
    }
    else if (state == GameState::Records) {
        recordsScreen->update();
    }
    else if (state == GameState::MainGame) {
        ball->update();
        platforma->update();
        check_collisions();
        score_text->update(std::to_string(score));

        // Проверяем, упал ли мяч ниже платформы
        sf::Vector2f ballPos = ball->getHitBox().getPosition();
        if (ballPos.y > SCREEN_HEIGHT) {
            saveScore();
            // Формируем текст конца игры
            std::string gameOverStr = u8"О ПОБЕДЕ ИЛИ ЗАВТРА... " /*+ std::to_string(score)*/;
            // Преобразуем UTF-8 в UTF-16 (std::wstring)
            int wideSize = MultiByteToWideChar(CP_UTF8, 0, gameOverStr.c_str(), -1, nullptr, 0);
            std::wstring wideStr(wideSize, 0);
            MultiByteToWideChar(CP_UTF8, 0, gameOverStr.c_str(), -1, &wideStr[0], wideSize);
            gameOverText->update(wideStr);
            gameOverText->centerHorizontally(SCREEN_WIDTH); // Центрируем по горизонтали
            gameOverText->centerVertically(SCREEN_HEIGHT);  // Центрируем по вертикали
            gameOverTimer.restart();
            state = GameState::GameOver;
        }
    }
    else if (state == GameState::GameOver) {
        // Ждём 3 секунды перед переходом в главное меню
        if (gameOverTimer.getElapsedTime().asSeconds() >= 3.f) {
            score = 0;
            ball->setSpeed(5.f, 5.f);
            ball->update();
            switchToMainMenu();
        }
    }
}

void Game::check_collisions() {
    // Проверяем столкновение мяча с платформой
    sf::FloatRect ballHitBox = ball->getHitBox();
    sf::FloatRect platformHitBox = platforma->getHitBox();

    if (ballHitBox.intersects(platformHitBox)) {
        sf::Vector2f ballPos = ball->getPosition();
        sf::Vector2f prevPos = ball->getPreviousPosition();
        float speedy = ball->getSpeedY();
        float speedx = ball->getSpeedX();

        // Определяем, с какой стороны мяч попал на платформу
        // Вычисляем пересечение по осям
        float overlapLeft = (ballHitBox.left + ballHitBox.width) - platformHitBox.left;
        float overlapRight = (platformHitBox.left + platformHitBox.width) - ballHitBox.left;
        float overlapTop = (ballHitBox.top + ballHitBox.height) - platformHitBox.top;
        float overlapBottom = (platformHitBox.top + platformHitBox.height) - ballHitBox.top;

        // Находим минимальное пересечение, чтобы определить сторону
        float minOverlapX = std::min(overlapLeft, overlapRight);
        float minOverlapY = std::min(overlapTop, overlapBottom);

        if (minOverlapY < minOverlapX) {
            // Столкновение сверху или снизу
            if (speedy > 0) { // Мяч движется вниз (попал сверху)
                ball->bounceVertical(); // Отскок по вертикали
                ball->setPosition(ballPos.x, platformHitBox.top - ballHitBox.height);
                score++;
            }
            else if (speedy < 0) { // Мяч движется вверх (попал снизу)
                ball->bounceVertical();
                ball->setPosition(ballPos.x, platformHitBox.top + platformHitBox.height);
            }
        }
        else {
            // Столкновение слева или справа
            if (speedx > 0) { // Мяч движется вправо (попал слева)
                ball->bounceHorizontal(); // Отскок по горизонтали
                ball->setPosition(platformHitBox.left - ballHitBox.width, ballPos.y);
                score++;
            }
            else if (speedx < 0) { // Мяч движется влево (попал справа)
                ball->bounceHorizontal();
                ball->setPosition(platformHitBox.left + platformHitBox.width, ballPos.y);
                score++;
            }
        }
    }
}

void Game::draw() {
    window->clear(currentTheme == Theme::Dark ? sf::Color::Black : sf::Color(250, 250, 250));

    if (state == GameState::Login) {
        loginScreen->draw(*window);
    }
    else if (state == GameState::Welcome) {
        welcomeScreen->draw(*window);
    }
    else if (state == GameState::MainMenu) {
        mainMenuScreen->draw(*window);
    }
    else if (state == GameState::ChooseDifficulty) {
        gameDifficultyScreen->draw(*window);
    }
    else if (state == GameState::Settings) {
        settingsScreen->draw(*window);
    }
    else if (state == GameState::Records) {
        recordsScreen->draw(*window);
    }
    else if (state == GameState::MainGame) {
        ball->draw(window);
        platforma->draw(window);
        score_text->draw(window);
    }
    else if (state == GameState::GameOver) {
        gameOverText->draw(window); // Отображаем текст конца игры
    }

    window->display();
}

void Game::play() {
    while (window->isOpen()) {
        check_events();
        update();
        check_collisions();
        draw();
    }
}

void Game::switchToMainMenu() {
    delete welcomeScreen;
    delete settingsScreen;
    delete loginScreen;
    delete recordsScreen;
    welcomeScreen = nullptr;
    settingsScreen = nullptr;
    loginScreen = nullptr;
    recordsScreen = nullptr;
    mainMenuScreen = new MainMenuScreen(font, &textureManager, this);
    currentScreen = mainMenuScreen;
    state = GameState::MainMenu;
}

void Game::switchToGame() {
    score = 0;
    ball->reset();
    platforma->reset();
    score_text->update(std::to_string(score));
    state = GameState::MainGame;
    delete gameDifficultyScreen;
    gameDifficultyScreen = nullptr;
    currentScreen = nullptr;
    std::cerr << u8"Начало игры: score=" << score
        << ", ballPos=" << ball->getPosition().x << "," << ball->getPosition().y
        << ", ballSpeed=" << ball->getSpeedX() << "," << ball->getSpeedY() << "\n";
}

void Game::switchToWelcomeScreen() {
    playerName = loginScreen->getPlayerName();
    std::cerr << u8"Имя игрока после ввода: " << playerName << "\n";
    welcomeScreen = new WelcomeScreen(font, textureManager.getTexture(currentTheme == Theme::Dark ? TEXTURE_SCREEN_DARK_BG_KEY : TEXTURE_SCREEN_LIGHT_BG_KEY),
        loginScreen->getPlayerName(), [this]() {
            switchToMainMenu();
        });
    currentScreen = welcomeScreen;
    state = GameState::Welcome;
    delete loginScreen;
    loginScreen = nullptr;
}

void Game::switchToChooseDifficulty() {
    gameDifficultyScreen = new GameDifficultyScreen(font,
        textureManager.getTexture(currentTheme == Theme::Dark ? TEXTURE_SCREEN_DARK_BG_KEY : TEXTURE_SCREEN_LIGHT_BG_KEY),
        this);
    currentScreen = gameDifficultyScreen;
    state = GameState::ChooseDifficulty;
    delete mainMenuScreen;
    mainMenuScreen = nullptr;
}

void Game::setBallSpeed(float speedx, float speedy) {
    ball->setSpeed(speedx, speedy);
}

void Game::setTheme(Theme newTheme, TextureManager* textureManager) {
    currentTheme = newTheme;
    saveTheme();
    if (state == GameState::Settings && textureManager && settingsScreen) {
        settingsScreen->updateBackground(textureManager->getTexture(currentTheme == Theme::Dark ? TEXTURE_SCREEN_DARK_BG_KEY : TEXTURE_SCREEN_LIGHT_BG_KEY));
    }
    else {
        updateScreenTheme();
    }
    // Обновляем текстуру мяча
    if (ball) {
        ball->updateTexture(textureManager->getTexture(
            currentTheme == Theme::Dark ? TEXTURE_DARK_BALL_KEY : TEXTURE_LIGHT_BALL_KEY));
    }
    // Обновляем текстуру платформы
    if (platforma) {
        platforma->updateTexture(textureManager->getTexture(
            currentTheme == Theme::Dark ? TEXTURE_DARK_PLATFORM_KEY : TEXTURE_LIGHT_PLATFORM_KEY));
    }
    if (score_text) {
        score_text->setColor(currentTheme == Theme::Dark ? sf::Color::White : sf::Color::Black);
    }
    // Обновляем цвет текста конца игры
    if (gameOverText) {
        gameOverText->setColor(currentTheme == Theme::Dark ? sf::Color::White : sf::Color::Black);
    }
}

void Game::switchToSettings() {
    settingsScreen = new SettingsScreen(font,
        textureManager.getTexture(currentTheme == Theme::Dark ? TEXTURE_SCREEN_DARK_BG_KEY : TEXTURE_SCREEN_LIGHT_BG_KEY),
        &textureManager,
        this);
    currentScreen = settingsScreen;
    state = GameState::Settings;
    delete mainMenuScreen;
    mainMenuScreen = nullptr;
}

void Game::updateScreenTheme() {
    if (currentScreen == nullptr) return;

    if (state == GameState::MainMenu) {
        delete mainMenuScreen;
        mainMenuScreen = new MainMenuScreen(font, &textureManager, this);
        currentScreen = mainMenuScreen;
    }
    else if (state == GameState::ChooseDifficulty) {
        delete gameDifficultyScreen;
        gameDifficultyScreen = new GameDifficultyScreen(font,
            textureManager.getTexture(currentTheme == Theme::Dark ? TEXTURE_SCREEN_DARK_BG_KEY : TEXTURE_SCREEN_LIGHT_BG_KEY),
            this);
        currentScreen = gameDifficultyScreen;
    }
    else if (state == GameState::Records) {
        delete recordsScreen;
        recordsScreen = new RecordsScreen(font,
            textureManager.getTexture(currentTheme == Theme::Dark ? TEXTURE_SCREEN_DARK_BG_KEY : TEXTURE_SCREEN_LIGHT_BG_KEY),
            this);
        currentScreen = recordsScreen;
    }
}

void Game::loadTheme() {
    std::ifstream file("theme.txt");
    if (file.is_open()) {
        int themeValue;
        if (file >> themeValue) {
            currentTheme = static_cast<Theme>(themeValue);
        }
        file.close();
    }
}

void Game::saveTheme() {
    std::ofstream file("theme.txt");
    if (file.is_open()) {
        file << static_cast<int>(currentTheme) << "\n";
        file.close();
    }
}

void Game::saveScore() {
    // Загружаем текущие рекорды
    loadRecords();

    // Проверяем, является ли текущий результат рекордным
    bool isRecord = false;
    if (records.size() < 5) {
        isRecord = true;
    }
    else {
        int minScore = records.back().second;
        if (score > minScore) {
            isRecord = true;
        }
    }

    if (isRecord) {
        // Проверяем, что имя игрока не пустое
        if (playerName.empty()) {
            std::cerr << u8"Ошибка: имя игрока пустое, рекорд не записан\n";
            return;
        }

        // Отладочный вывод
        std::cerr << u8"Записываем рекорд: имя=" << playerName << u8", счёт=" << score << "\n";
        records.emplace_back(playerName, score);
        std::sort(records.begin(), records.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });
        if (records.size() > 5) {
            records.resize(5);
        }
        saveRecords();
    }
}

void Game::switchToRecords() {
    recordsScreen = new RecordsScreen(font, textureManager.getTexture(currentTheme == Theme::Dark ? TEXTURE_SCREEN_DARK_BG_KEY : TEXTURE_SCREEN_LIGHT_BG_KEY), this);
    currentScreen = recordsScreen;
    state = GameState::Records;
    delete mainMenuScreen;
    mainMenuScreen = nullptr;
}

void Game::loadRecords() {
    std::ifstream file("records.txt", std::ios::binary);
    records.clear();

    if (!file.is_open()) {
        std::cerr << u8"Файл records.txt не найден, таблица рекордов пуста\n";
        return;
    }

    // Пропускаем BOM, если он есть
    char bom[3];
    file.read(bom, 3);
    if (bom[0] != char(0xEF) || bom[1] != char(0xBB) || bom[2] != char(0xBF)) {
        file.seekg(0); // Если BOM нет, возвращаемся в начало
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Разбиваем содержимое на строки
    std::stringstream iss(content); // Используем std::stringstream вместо std::istringstream
    std::string line;
    while (std::getline(iss, line)) {
        std::stringstream lineStream(line);
        std::string name;
        int score;
        if (lineStream >> name >> score) {
            records.emplace_back(name, score);
        }
    }

    if (records.empty()) {
        std::cerr << u8"Файл records.txt пуст, таблица рекордов пуста\n";
    }

    // Сортируем по убыванию очков
    std::sort(records.begin(), records.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    // Ограничиваем топ-5
    if (records.size() > 5) {
        records.resize(5);
    }
}

void Game::saveRecords() {
    // Открываем файл в бинарном режиме
    std::ofstream file("records.txt", std::ios::binary);
    if (file.is_open()) {
        // Записываем BOM для UTF-8
        const char bom[] = { char(0xEF), char(0xBB), char(0xBF) };
        file.write(bom, sizeof(bom));

        // Записываем данные
        for (const auto& [name, score] : records) {
            file << name << " " << score << "\n";
        }
        file.close();
    }
}

Game::~Game() {
    delete window;
    delete ball;
    delete platforma;
    delete score_text;
    delete gameOverText;
    delete currentScreen;
    delete loginScreen;
    delete mainMenuScreen;
    delete gameDifficultyScreen;
    delete welcomeScreen;
    delete settingsScreen;
    delete recordsScreen;
}