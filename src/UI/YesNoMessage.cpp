#include "YesNoMessage.h"
#include "../Application.h"
#include "../tools/ResourceManager.h"
#include "../tools/AudioOneShotEngine.h"

YesNoMessage::YesNoMessage(YesNoMessage::tAction yes, YesNoMessage::tAction no, const std::string &message)
    : GenericWindow(message, "Decide!", ResourceManager::get().getTexture("message.png"))
    , yes{ Application::get().getMidPoint() + sf::Vector2f(0, 200), std::move(yes), "Yes" }
    , no{ Application::get().getMidPoint() + sf::Vector2f(0, 270), std::move(no), "No" }
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
    AudioOneShotEngine::get().play("yes.wav");
    return true;
  }

  if(no.onEvent(e))
  {
    AudioOneShotEngine::get().play("no.wav");
    return true;
  }

  return GenericWindow::onEvent(e);
}
