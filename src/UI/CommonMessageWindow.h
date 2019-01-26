#pragma once
#include "GenericWindow.h"
#include "Button.h"

class CommonMessageWindow : public GenericWindow {
public:
    CommonMessageWindow(const std::string &message, const std::string& header);
    void draw(sf::RenderWindow& window) override;
    void onEvent(sf::Event& e) override;
protected:
    Button ok;
};