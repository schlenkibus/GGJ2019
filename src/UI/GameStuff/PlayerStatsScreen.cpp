#include "PlayerStatsScreen.h"
#include "../../tools/ResourceManager.h"
#include "../../Game/GameStateManager.h"

PlayerStatsScreen::PlayerStatsScreen()
    : GenericOkayWindowWithCallback{ "Weekly Roundup \n" + GameStateManager::get().getWeeklyReport(), "Okay",
                                     [] { if(GameStateManager::get().getCurrentMoney() > 0) GameStateManager::get().setScreenState(ScreenState::NewTenant); else GameStateManager::get().setScreenState(ScreenState::GameOver); } }
{
    sprite.setColor(sf::Color::Red);
}
