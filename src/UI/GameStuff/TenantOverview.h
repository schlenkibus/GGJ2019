#pragma once
#include "../generic/DrawableObject.h"
#include "../../Data/TenantData.h"
#include "../generic/Button.h"

class TenantOverview : public DrawableObject
{
 public:
  TenantOverview(TenantData* data, sf::Vector2f pos);
  void draw(sf::RenderWindow& window) override;
  bool onEvent(sf::Event& e) override;

 public:
  TenantData* info;
  sf::Text text;
};