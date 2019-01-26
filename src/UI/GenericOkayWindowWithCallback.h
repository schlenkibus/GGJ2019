#pragma once

#include "GenericWindow.h"
#include "Button.h"

class GenericOkayWindowWithCallback : public GenericWindow
{
 public:
  GenericOkayWindowWithCallback(std::string message, std::string buttonText, std::function<void(void)> okayAction);
  bool onEvent(sf::Event& e) override;
  void draw(sf::RenderWindow& window) override;

 protected:
  Button ok;
};
