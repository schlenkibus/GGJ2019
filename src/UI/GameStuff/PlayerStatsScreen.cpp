#include "PlayerStatsScreen.h"
#include "../../tools/ResourceManager.h"
#include "../../Game/GameStateManager.h"
#include "../../Application.h"

PlayerStatsScreen::PlayerStatsScreen()
    : GenericOkayWindowWithCallback{ "Weekly Roundup \n" + GameStateManager::get().getWeeklyReport(), "Okay", [] {
                                      if(GameStateManager::get().getCurrentMoney() > 0)
                                        GameStateManager::get().setScreenState(ScreenState::NewTenant);
                                      else
                                        GameStateManager::get().setScreenState(ScreenState::GameOver);
                                    } }
{
  sprite.setColor(sf::Color::Red);

  auto data = GameStateManager::get().getCopyOfCurrentTenant();
  for(int i = 0; i < data.size(); i++)
  {
      if (i < 5)
      {
          m_currentTenants[i] = std::make_unique<TenantOverview>(
                  data[i].get(), Application::get().getMidPoint() + sf::Vector2f(-380, -200 + (100 * i)));
          m_currentTenants[i]->scale(0.15);
      }
      else
      {
          m_currentTenants[i] = std::make_unique<TenantOverview>(
                  data[i].get(), Application::get().getMidPoint() + sf::Vector2f(350, -200 + (100 * (i - 5))));
          m_currentTenants[i]->scale(0.15);
      }
  }
}

void PlayerStatsScreen::draw(sf::RenderWindow& window)
{
  GenericWindow::draw(window);
  for(auto& e : m_currentTenants)
  {
    e->draw(window);
  }
  GenericOkayWindowWithCallback::draw(window);
}