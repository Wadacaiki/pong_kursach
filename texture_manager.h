#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "settings.h" // Для Theme


class TextureManager {
private:
    std::unordered_map<std::string, sf::Texture> textures;

public:
    // Загружает текстуру по имени
    bool loadTexture(const std::string& name, const std::string& filename);

    // Получает текстуру по имени
    const sf::Texture& getTexture(const std::string& name) const;

    // Проверяет наличие текстуры
    bool hasTexture(const std::string& name) const;
};
