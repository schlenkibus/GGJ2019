#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <functional>

class DrawableObject {
public:
    typedef std::function<void(sf::Event&, DrawableObject&)> tEventCB;
    typedef std::function<void(float, DrawableObject&)> tUpdateCB;

    DrawableObject(sf::Texture& tex, sf::Vector2f pos);
    DrawableObject(sf::Texture& tex, sf::Vector2f pos, tEventCB onEventCB, tUpdateCB onUpdateCB);
    void draw(sf::RenderWindow& window);
    void onEvent(sf::Event& e);
    void update(float delta);
protected:
    sf::Sprite sprite;
    sf::Texture& tex;
    tUpdateCB updateCB;
    tEventCB onEventCB;
};