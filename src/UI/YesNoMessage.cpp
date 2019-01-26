#include "YesNoMessage.h"
#include "../Application.h"
#include "../tools/ResourceManager.h"

YesNoMessage::YesNoMessage(YesNoMessage::tAction yes, YesNoMessage::tAction no, const std::string &message)
    : GenericWindow(message, "Decide!", ResourceManager::get().getTexture("message.png"))
    , yes{ Application::get().getMidPoint() + sf::Vector2f(0, 200), std::move(yes), "Yes" }
    , no{ Application::get().getMidPoint() + sf::Vector2f(0, 270), std::move(no), "No" }
{
}

void YesNoMessage::draw(sf::RenderWindow &w)
{
  GenericWindow::draw(w);
  no.draw(w);
  yes.draw(w);
}

bool YesNoMessage::onEvent(sf::Event &e)
{
  bool eventUsed = false;
  eventUsed = eventUsed | yes.onEvent(e);
  eventUsed = eventUsed | no.onEvent(e);
  return eventUsed | GenericWindow::onEvent(e);
}
