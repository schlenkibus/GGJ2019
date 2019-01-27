#include "YesNoMessage.h"
#include "../../Application.h"
#include "../../tools/ResourceManager.h"
#include "../../tools/AudioOneShotEngine.h"

YesNoMessage::YesNoMessage(YesNoMessage::tAction yes, YesNoMessage::tAction no, const std::string &message)
    : GenericWindow(message, "Decide!", ResourceManager::get().getTexture("Paper.png"))
    , yes{ Application::get().getMidPoint() + sf::Vector2f(-70, 270), std::move(yes), "" }
    , no{ Application::get().getMidPoint() + sf::Vector2f(70, 270), std::move(no), "" }
{
  this->yes.setTexture(ResourceManager::get().getTexture("green_button01.png"));
  this->no.setTexture(ResourceManager::get().getTexture("red_button01.png"));
}

void YesNoMessage::draw(sf::RenderWindow &w)
{
  GenericWindow::draw(w);
  no.draw(w);
  yes.draw(w);
}

bool YesNoMessage::onEvent(sf::Event &e)
{
  if(yes.onEvent(e))
  {
    return true;
  }

  if(no.onEvent(e))
  {
    return true;
  }

  return GenericWindow::onEvent(e);
}
