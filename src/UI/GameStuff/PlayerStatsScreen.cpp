#include "PlayerStatsScreen.h"
#include "../../tools/ResourceManager.h"
#include "../../Game/GameStateManager.h"

PlayerStatsScreen::PlayerStatsScreen()
    : GenericOkayWindowWithCallback{ "Weekly Roundup \n" + GameStateManager::get().getWeeklyReport(), "Okay",
                                     [] { GameStateManager::get().setScreenState(ScreenState::NewTenant); } }
{
}
