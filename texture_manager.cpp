#include "texture_manager.h"
#include <iostream>

bool TextureManager::loadTexture(const std::string& name, const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Ошибка загрузки текстуры: " << filename << std::endl;
        return false;
    }
    textures[name] = std::move(texture);
    return true;
}

const sf::Texture& TextureManager::getTexture(const std::string& name) const {
    auto it = textures.find(name);
    if (it == textures.end()) {
        throw std::runtime_error("Текстура с именем \"" + name + "\" не найдена");
    }
    return it->second;
}

bool TextureManager::hasTexture(const std::string& name) const {
    return textures.find(name) != textures.end();
}
