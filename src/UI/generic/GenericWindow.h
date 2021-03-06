#pragma once
#include "DrawableObject.h"

class GenericWindow : public DrawableObject
{
 public:
  GenericWindow(const std::string &message, const std::string &header, sf::Texture &tex);
  void draw(sf::RenderWindow &window) override;
  bool onEvent(sf::Event &e) override;

 protected:
  const size_t charactersToNewLine();
  sf::Text m_header;
  sf::Text m_message;
};