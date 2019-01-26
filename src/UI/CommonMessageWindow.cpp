#include "CommonMessageWindow.h"
#include "../Application.h"
#include "../tools/ResourceManager.h"

CommonMessageWindow::CommonMessageWindow(const std::string &message, const std::string &header)
    : GenericWindow(message, header, ResourceManager::get().getTexture("message.png"))
    , ok{ Application::get().getMidPoint() + sf::Vector2f(0, 250),
          []() { Application::get().getLevel().closeMessage(); }, "Okay!" }
{
}

void CommonMessageWindow::draw(sf::RenderWindow &window)
{
  GenericWindow::draw(window);
  ok.draw(window);
}

bool CommonMessageWindow::onEvent(sf::Event &e)
{
  if(ok.onEvent(e))
    return true;
  return GenericWindow::onEvent(e);
}
