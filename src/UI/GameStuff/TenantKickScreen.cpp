#include "TenantKickScreen.h"

TenantKickScreen::TenantKickScreen()
    : GenericWindow("You have to throw one Tenant out to make room for the new one!", "DECIDE!",
                    ResourceManager::get().getTexture("message_3times.png"))
{

  auto data = GameStateManager::get().getKickCandidates();
  for(int i = 0; i < 3; i++)
  {
    m_candidates[i] = std::make_unique<TenantKickEntry>(data[i], Application::get().getMidPoint()
                                                            + sf::Vector2f((-300 + i * 150), 0));
  }
}

void TenantKickScreen::draw(sf::RenderWindow& window)
{
  GenericWindow::draw(window);
  for(auto& e : m_candidates)
  {
    e->draw(window);
  }
}

bool TenantKickScreen::onEvent(sf::Event& e)
{
  for(auto& c : m_candidates)
  {
    if(c->onEvent(e))
      return true;
  }
  return GenericWindow::onEvent(e);
}
