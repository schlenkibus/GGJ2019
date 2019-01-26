#pragma once
#include <unordered_map>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class ResourceManager {
public:
    const char* prefix = "../resources/";
    typedef std::string tPath;
    static ResourceManager& get();
    sf::Texture& getTexture(tPath path);
    sf::Font& getFont();
protected:
    ResourceManager();
    std::unordered_map<tPath, sf::Texture> m_texture;
    sf::Font m_font;
};
