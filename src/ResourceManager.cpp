#include <iostream>
#include "ResourceManager.h"
#include <experimental/filesystem>

ResourceManager &ResourceManager::get() {
    static ResourceManager rm;
    return rm;
}

sf::Texture &ResourceManager::getTexture(tPath path) {
    path = prefix + path;
    try {
        return m_texture.at(path);
    } catch(...) {
        auto& tex = m_texture[path];
        auto ret = tex.loadFromFile(path);
        if(!ret) {
            std::cerr << std::experimental::filesystem::current_path() << std::endl;
            std::cerr << "could not load texture from: " << path << '\n';
            exit(60);
        }
        return tex;
    }
}

sf::Font &ResourceManager::getFont() {
    return m_font;
}

ResourceManager::ResourceManager() {
    if(!m_font.loadFromFile(std::string(prefix) + "BitCasual.ttf")) {
        std::cerr << std::experimental::filesystem::current_path() << std::endl;
        std::cerr << "could not load texture from: BitCasual.ttf" << '\n';
    }
}
