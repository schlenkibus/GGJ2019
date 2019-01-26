#include "YesNoMessage.h"
#include "../Application.h"

YesNoMessage::YesNoMessage(YesNoMessage::tAction yes, YesNoMessage::tAction no, const std::string &message) :
MessageWindow(message, "Decide!"), yes{Application::get().getMidPoint() + sf::Vector2f(0, 200), std::move(yes), "Yes"},
no{Application::get().getMidPoint() + sf::Vector2f(0, 270), std::move(no), "No"}{
}

void YesNoMessage::draw(sf::RenderWindow &w) {
    MessageWindow::draw(w);
    no.draw(w);
    yes.draw(w);
}

void YesNoMessage::onEvent(sf::Event &e) {
    yes.onEvent(e);
    no.onEvent(e);
    MessageWindow::onEvent(e);
}
