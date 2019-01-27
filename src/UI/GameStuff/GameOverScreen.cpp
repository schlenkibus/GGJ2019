#include "GameOverScreen.h"
#include "../../Game/GameStateManager.h"
#include "../../Application.h"
#include "../../tools/AudioOneShotEngine.h"
#include "../../tools/ResourceManager.h"

GameOverScreen::GameOverScreen()
    : GenericOkayWindowWithCallback{ GameStateManager::get().getGameOverMessage(), DataManager::get().getSadOkay(),
                                     []() { Application::get().getLevel().setMenuScene(); } }
{
  AudioOneShotEngine::get().play("new3.wav");
}
