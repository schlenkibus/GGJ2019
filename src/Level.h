#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Game/DrawableObject.h"

class Level {
public:
    Level();
    void update(float delta);
    void onEvent(sf::Event& e);
    void draw(sf::RenderWindow& w);
protected:
    std::vector<DrawableObject> m_objects;
};
