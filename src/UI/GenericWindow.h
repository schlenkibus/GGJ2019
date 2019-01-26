#pragma once
#include "../Game/DrawableObject.h"

class GenericWindow : public DrawableObject
{
 public:
  GenericWindow(const std::string &message, const std::string &header, sf::Texture &tex);
  void draw(sf::RenderWindow &window) override;
  void onEvent(sf::Event &e) override;

 protected:
  sf::Text m_header;
  sf::Text m_message;
};