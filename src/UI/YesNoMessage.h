#pragma once
#include "GenericWindow.h"
#include "Button.h"

class YesNoMessage : public GenericWindow
{
 public:
  typedef std::function<void(void)> tAction;
  YesNoMessage(tAction yes, tAction no, const std::string &message);
  void draw(sf::RenderWindow &w) override;
  bool onEvent(sf::Event &e) override;

 protected:
  Button yes;
  Button no;
};
