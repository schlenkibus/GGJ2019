#pragma once
#include "MessageWindow.h"

class YesNoMessage : public MessageWindow {
public:
    typedef std::function<void(void)> tAction;
    YesNoMessage(tAction yes, tAction no, const std::string& message);
    void draw(sf::RenderWindow& w) override;
    void onEvent(sf::Event& e) override;
protected:
    Button yes;
    Button no;
};
