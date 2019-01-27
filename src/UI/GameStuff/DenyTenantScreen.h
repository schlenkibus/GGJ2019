#pragma once
#include "../generic/GenericOkayWindowWithCallback.h"

class DenyTenantScreen : public GenericOkayWindowWithCallback
{
 public:
  DenyTenantScreen();
  void draw(sf::RenderWindow& window) override;

 protected:
  DrawableObject pic;
};

class AfterKickTenantScreem : public GenericOkayWindowWithCallback
{
 public:
  AfterKickTenantScreem();
  void draw(sf::RenderWindow& window) override;

 protected:
  DrawableObject pic;
};
