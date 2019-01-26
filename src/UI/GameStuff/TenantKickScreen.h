#pragma once
#include "../generic/GenericWindow.h"
#include "../../tools/ResourceManager.h"
#include "../../Data/TenantData.h"
#include "../../Application.h"
#include "../../Game/GameStateManager.h"
#include "TenantKickEntry.h"

class TenantKickScreen : public GenericWindow
{
 public:
  explicit TenantKickScreen();
  void draw(sf::RenderWindow& window) override;
  bool onEvent(sf::Event& e) override;

 protected:
  std::array<std::unique_ptr<TenantKickEntry>, 3> m_candidates;
};