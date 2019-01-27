#pragma once
#include "../generic/DrawableObject.h"
#include "../generic/GenericWindow.h"
#include "../generic/Button.h"
#include "../generic/GenericOkayWindowWithCallback.h"
#include "../../UI/GameStuff/TenantOverview.h"
#include "../../Data/TenantData.h"

#include <array>

class PlayerStatsScreen : public GenericOkayWindowWithCallback
{
  public:
    PlayerStatsScreen();
    void draw(sf::RenderWindow& window) override;

  private:
    std::array<std::unique_ptr<TenantOverview>, 10> m_currentTenants;
};