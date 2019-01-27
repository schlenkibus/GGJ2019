#include "GameOverScreen.h"
#include "../../Game/GameStateManager.h"
#include "../../Application.h"

GameOverScreen::GameOverScreen() : GenericOkayWindowWithCallback{GameStateManager::get().getGameOverMessage(), DataManager::get().getSadOkay(), [](){
    Application::get().getLevel().setMenuScene();
}} {
}
