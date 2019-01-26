#include "DayChangeWindow.h"
#include "../../Game/GameStateManager.h"

DayChangeWindow::DayChangeWindow()
    : GenericOkayWindowWithCallback{ "Day " + std::to_string(GameStateManager::get().getDay()), "Okay", []() {
                                      //Next Day GameStateManager::get().
                                    } }
{
}
