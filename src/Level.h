#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Game/DrawableObject.h"
#include "UI/MessageWindow.h"

class Level {
public:
    Level();
    void update(float delta);
    void onEvent(sf::Event& e);
    void draw(sf::RenderWindow& w);
    void pushMessage(const std::string &message);
    void closeMessage();
protected:
    std::vector<std::unique_ptr<DrawableObject>> m_objects;
    std::unique_ptr<MessageWindow> m_message;
};
