#pragma once

#include "DrawableObject.h"
#include <functional>

class Button : public DrawableObject
{
 public:
  typedef std::function<void(Button &)> tHoverCallBack;
  Button(sf::Vector2f pos, std::function<void(void)> action, const std::string &text);
  void draw(sf::RenderWindow &window) override;
  bool onEvent(sf::Event &e) override;
  void setTexture(sf::Texture &tex);
  void listenToOnHoverEnd(tHoverCallBack);
  void listenToOnHoverStart(tHoverCallBack);

 protected:
  tHoverCallBack m_onHoverExit;
  tHoverCallBack m_onHoverStart;
  sf::Text m_text;
  std::function<void(void)> m_action;
};