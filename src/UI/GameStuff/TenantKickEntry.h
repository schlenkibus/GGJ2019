#pragma once
#include "../generic/DrawableObject.h"
#include "../../Data/TenantData.h"
#include "../generic/Button.h"

class TenantKickEntry : public DrawableObject
{
 public:
  TenantKickEntry(TenantData* data, sf::Vector2f pos);
  void draw(sf::RenderWindow& window) override;
  bool onEvent(sf::Event& e) override;
  TenantData* info;
  sf::Text text;
  Button kick;
};