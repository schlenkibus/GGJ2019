#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Game/DrawableObject.h"
#include "UI/MessageWindow.h"
#include "UI/YesNoMessage.h"

class Level {
public:
    Level();
    void update(float delta);
    void onEvent(sf::Event& e);
    void draw(sf::RenderWindow& w);
    void pushMessage(const std::string &message);
    void pushYesNoMessage(const std::string& message, YesNoMessage::tAction yes, YesNoMessage::tAction no);
    void closeMessage();
protected:
    std::vector<std::unique_ptr<DrawableObject>> m_objects;
    std::unique_ptr<MessageWindow> m_message;
};
