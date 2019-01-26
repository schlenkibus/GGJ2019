#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>

class DrawableObject
{
 public:
  typedef std::function<bool(sf::Event &, DrawableObject &)> tEventCB;
  typedef std::function<void(float, DrawableObject &)> tUpdateCB;

  DrawableObject(sf::Texture &tex, sf::Vector2f pos);
  DrawableObject(sf::Texture &tex, sf::Vector2f pos, tEventCB onEventCB, tUpdateCB onUpdateCB);
  virtual void draw(sf::RenderWindow &window);
  virtual bool onEvent(sf::Event &e);
  virtual void update(float delta);

  bool contains(sf::Vector2i pos) const;
  void setPos(sf::Vector2f pos);

 protected:
  sf::Sprite sprite;
  sf::Texture &tex;
  tUpdateCB updateCB;
  tEventCB onEventCB;
};