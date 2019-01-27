#pragma once

#include <SFML/Graphics.hpp>

class CashView : public sf::Text
{
 public:
  CashView();
  CashView(int initalValue, sf::Vector2f position);
  void setCash(int newValue);
};