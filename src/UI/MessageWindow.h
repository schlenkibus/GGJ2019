#pragma once
#include "../Game/DrawableObject.h"
#include "Button.h"

class MessageWindow : public DrawableObject {
public:
    MessageWindow(const std::string &message, const std::string& header);
    void draw(sf::RenderWindow& window) override;
    void onEvent(sf::Event& e) override;
protected:
    sf::Text m_header;
    sf::Text m_message;
};