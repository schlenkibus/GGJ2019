#include "DenyTenantScreen.h"
#include "../generic/GenericOkayWindowWithCallback.h"
#include "../../Game/GameStateManager.h"
#include "../../Application.h"

DenyTenantScreen::DenyTenantScreen()
    : GenericOkayWindowWithCallback{ GameStateManager::get().getTenant()->getOutcome(), "I feel bad now",
                                     []() { GameStateManager::get().setScreenState(ScreenState::NewTenant); } }
    , pic{ GameStateManager::get().getTenant()->getTexture(), Application::get().getMidPoint() + sf::Vector2f(200, 0) }
{
  pic.scale(0.5);
}

void DenyTenantScreen::draw(sf::RenderWindow &window)
{
  GenericOkayWindowWithCallback::draw(window);
  pic.draw(window);
}
