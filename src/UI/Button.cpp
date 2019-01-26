#include "Button.h"
#include "../Application.h"
#include "../tools/ResourceManager.h"
#include "../tools/AudioOneShotEngine.h"
#include <iostream>
#include <utility>

Button::Button(sf::Vector2f pos, std::function<void(void)> action, const std::string &text)
    : DrawableObject(ResourceManager::get().getTexture("button.png"), pos)
    , m_action{ std::move(action) }
{
  m_text.setPosition(pos.x - tex.getSize().x / 3.5f, pos.y - tex.getSize().y / 2.f);
  m_text.setString(text);
  m_text.setCharacterSize(40);
  m_text.setFillColor(sf::Color::White);
  m_text.setOutlineThickness(2);
  m_text.setOutlineColor(sf::Color::Black);
  m_text.setFont(ResourceManager::get().getFont());
}

void Button::draw(sf::RenderWindow &window)
{
  DrawableObject::draw(window);
  window.draw(m_text);
}

void Button::setTexture(sf::Texture& tex) {
  sprite.setTexture(tex);
}

bool Button::onEvent(sf::Event &e)
{
  bool ret = false;
  auto mousePos = Application::get().getMouse();

  if(e.type == sf::Event::MouseMoved)
  {
    if(sprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
      sprite.setScale(1.1, 1.1);
      m_text.setCharacterSize(45);
    }
    else
    {
      m_text.setCharacterSize(40);
      sprite.setScale(1, 1);
    }
  }
  if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left)
  {
    if(sprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
      AudioOneShotEngine::get().play("testSound.wav");
      m_action();
      ret = true;
    }
    sprite.setColor(sf::Color::White);
  }

  if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Button::Left)
  {
    if(sprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
      sprite.setColor(sf::Color::Green);
    }
  }
  return ret;
}
