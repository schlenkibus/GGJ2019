#include "Title.h"
#include "../../tools/ResourceManager.h"

Title::Title(sf::Vector2f pos, const std::string &text)
        : DrawableObject(ResourceManager::get().getTexture("test.png"), pos)
{
    m_text.setOutlineThickness(2);
    m_text.setFont(ResourceManager::get().getFont());
    m_text.setString(text);
    m_text.setCharacterSize(50);
    m_text.setPosition(pos.x - m_text.getGlobalBounds().width / 2, pos.y - m_text.getGlobalBounds().height / 1.5f);
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineColor(sf::Color::Black);
}

void Title::draw(sf::RenderWindow &window)
{
    DrawableObject::draw(window);
    window.draw(m_text);
}

void Title::setTexture(sf::Texture &tex)
{
    sprite.setTexture(tex);
    sprite.setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f);
    sprite.setTextureRect(sf::Rect<int>(0, 0, tex.getSize().x, tex.getSize().y));
}

void Title::setCharSize(size_t s) {
    auto widthOld = m_text.getGlobalBounds().width;
    m_text.setCharacterSize(s);
    m_text.move((widthOld - m_text.getGlobalBounds().width) / 2, 0);
}
