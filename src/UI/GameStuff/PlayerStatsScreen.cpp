#include "PlayerStatsScreen.h"
#include "../../tools/ResourceManager.h"
#include "../../Game/GameStateManager.h"

PlayerStatsScreen::PlayerStatsScreen()
: GenericOkayWindowWithCallback{"Weekly roundup", "Okay", []{GameStateManager::get().setScreenState(ScreenState::NewTenant);}}
{
}
