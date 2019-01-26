#include "TenantView.h"
#include "../../Application.h"
#include "../../Game/GameStateManager.h"

TenantView::TenantView(TenantData& ref)
    : YesNoMessage(
          []() {
            GameStateManager::get().acceptTenant();
            GameStateManager::get().setScreenState(ScreenState::KickTenant);
          },
          [&]() {
            Application::get().getLevel().pushGenericMessage(ref.getOutcome(), []() {
              GameStateManager::get().declineTenant();
              GameStateManager::get().setScreenState(ScreenState::DenyTenant);
            });
          },
          ref.toString())
    , picture{ ref.getTexture(), Application::get().getMidPoint() + sf::Vector2f(300, 0) }
{
  picture.scale(0.5);
}

void TenantView::draw(sf::RenderWindow& window)
{
  YesNoMessage::draw(window);
  picture.draw(window);
}
