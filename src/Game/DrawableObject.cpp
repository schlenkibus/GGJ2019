#include <utility>

#include <utility>

#include <utility>

#include "DrawableObject.h"

DrawableObject::DrawableObject(sf::Texture &tex, sf::Vector2f pos)
    : tex{ tex }
    , onEventCB{ nullptr }
    , updateCB{ nullptr }
{
  sprite.setTexture(tex);
  sprite.setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f);
  sprite.setPosition(pos);
}

DrawableObject::DrawableObject(sf::Texture &tex, sf::Vector2f pos, DrawableObject::tEventCB onEventCB,
                               DrawableObject::tUpdateCB onUpdateCB)
    : tex{ tex }
    , updateCB{ std::move(onUpdateCB) }
    , onEventCB{ std::move(onEventCB) }
{
  sprite.setTexture(tex);
  sprite.setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f);
  sprite.setPosition(pos);
}

void DrawableObject::draw(sf::RenderWindow &window)
{
  window.draw(sprite);
}

void DrawableObject::onEvent(sf::Event &e)
{
  if(onEventCB)
  {
    onEventCB(e, *this);
  }
}

void DrawableObject::update(float delta)
{
  if(updateCB)
  {
    updateCB(delta, *this);
  }
}
