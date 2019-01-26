#include "TenantView.h"
#include "../Application.h"
#include "../tools/GameStateManager.h"

TenantView::TenantView(TenantData& ref)
    : YesNoMessage(
          []() {
            Application::get().getLevel().pushGenericMessage("Happy", []() { GameStateManager::get().acceptTenant(); });
          },
          [&]() {
            Application::get().getLevel().pushGenericMessage(ref.getOutcome(),
                                                             []() { GameStateManager::get().declineTenant(); });
          },
          ref.toString())
{
}
