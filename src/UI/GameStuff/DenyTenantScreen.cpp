#include "DenyTenantScreen.h"
#include "../generic/GenericOkayWindowWithCallback.h"
#include "../../Game/GameStateManager.h"
#include "../../Application.h"

DenyTenantScreen::DenyTenantScreen()
    : GenericOkayWindowWithCallback{ GameStateManager::get().getTenant()->getOutcome(), DataManager::get().getSadOkay(),
                                     []() { GameStateManager::get().setScreenState(ScreenState::NewTenant); } }
    , pic{ GameStateManager::get().getTenant()->getTexture(), Application::get().getMidPoint() + sf::Vector2f(400, 0) }
{
  pic.scale(0.5);
}

void DenyTenantScreen::draw(sf::RenderWindow &window)
{
  GenericOkayWindowWithCallback::draw(window);
  pic.draw(window);
}

AfterKickTenantScreem::AfterKickTenantScreem()
    : GenericOkayWindowWithCallback{ GameStateManager::get().getKickedTenant()->getOutcome(), DataManager::get().getSadOkay(),
                                     []() { GameStateManager::get().setScreenState(ScreenState::NewTenant); } }
    , pic{ GameStateManager::get().getTenant()->getTexture(), Application::get().getMidPoint() + sf::Vector2f(400, 0) }
{
  pic.scale(0.5);
}

void AfterKickTenantScreem::draw(sf::RenderWindow &window)
{
  GenericOkayWindowWithCallback::draw(window);
  pic.draw(window);
}