#pragma once

#include <functional>
#include "../Game/DrawableObject.h"

class Button : public DrawableObject {
public:
    Button(sf::Vector2f pos, std::function<void(void)> action, const std::string &text);
    void draw(sf::RenderWindow& window) override;
    void onEvent(sf::Event& e) override;
protected:
    sf::Text m_text;
    std::function<void(void)> m_action;
};