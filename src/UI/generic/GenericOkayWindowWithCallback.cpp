#include "GenericOkayWindowWithCallback.h"
#include "../../tools/ResourceManager.h"
#include "../../Application.h"

GenericOkayWindowWithCallback::GenericOkayWindowWithCallback(std::string message, std::string buttonText,
                                                             std::function<void(void)> okayAction)
    : GenericWindow{ message, "", ResourceManager::get().getTexture("message.png") }
    , ok{ Application::get().getMidPoint() + sf::Vector2f(0, 250), std::move(okayAction), buttonText }
{
}

bool GenericOkayWindowWithCallback::onEvent(sf::Event &e)
{
  if(ok.onEvent(e))
    return true;
  return GenericWindow::onEvent(e);
}

void GenericOkayWindowWithCallback::draw(sf::RenderWindow &window)
{
  GenericWindow::draw(window);
  ok.draw(window);
}
