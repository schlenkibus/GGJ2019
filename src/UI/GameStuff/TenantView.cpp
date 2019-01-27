#include "TenantView.h"
#include "../../Application.h"
#include "../../Game/GameStateManager.h"
#include "../../tools/AudioOneShotEngine.h"

TenantView::TenantView(TenantData& ref)
    : YesNoMessage(
          []() {
            GameStateManager::get().acceptTenant();
            GameStateManager::get().setScreenState(ScreenState::KickTenant);
          },
          [&]() {
            GameStateManager::get().declineTenant();
            GameStateManager::get().setScreenState(ScreenState::DenyTenant);
          },
          ref.toString())
    , picture{ ref.getTexture(), Application::get().getMidPoint() + sf::Vector2f(-400, 0) }
{
  AudioOneShotEngine::get().play("new2.wav");

  picture.scale(0.5);
}

void TenantView::draw(sf::RenderWindow& window)
{
  YesNoMessage::draw(window);
  picture.draw(window);
}
