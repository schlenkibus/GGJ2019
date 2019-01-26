#pragma once

#include "YesNoMessage.h"
#include "../Data/TenantData.h"

class TenantView : public YesNoMessage
{
 public:
  TenantView(TenantData& ref);
  void draw(sf::RenderWindow& window) override;
protected:
    DrawableObject picture;
};