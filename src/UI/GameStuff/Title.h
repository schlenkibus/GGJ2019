#pragma once
#include "../generic/DrawableObject.h"


class Title : public DrawableObject {
public:
    Title(sf::Vector2f pos, const std::string &text);
    void draw(sf::RenderWindow &window) override;
    void setTexture(sf::Texture &tex);
    void setCharSize(size_t s);
protected:
    sf::Text m_text;
};
