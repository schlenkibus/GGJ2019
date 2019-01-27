#pragma once
#include "../generic/DrawableObject.h"


class Title : public DrawableObject {
public:
    Title(sf::Vector2f pos, const std::string &text);
    void draw(sf::RenderWindow &window) override;
    void setTexture(sf::Texture &tex);
protected:
    sf::Text m_text;
};
