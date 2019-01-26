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
