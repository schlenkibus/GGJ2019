#pragma once
#include "Button.h"
#include "GenericWindow.h"

class CommonMessageWindow : public GenericWindow
{
 public:
  CommonMessageWindow(const std::string &message, const std::string &header);
  void draw(sf::RenderWindow &window) override;
  void onEvent(sf::Event &e) override;

 protected:
  Button ok;
};