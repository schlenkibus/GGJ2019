#pragma once
#include "../Game/DrawableObject.h"

class MessageWindow : public DrawableObject {
public:
    MessageWindow(const std::string& message);
    void draw(sf::RenderWindow& window) override;
    void onEvent(sf::Event& e) override;
protected:
    sf::Text m_header;
    sf::Text m_message;
};