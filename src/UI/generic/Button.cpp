#include "Button.h"
#include "../../Application.h"
#include "../../tools/ResourceManager.h"
#include "../../tools/AudioOneShotEngine.h"
#include <iostream>
#include <utility>

Button::Button(sf::Vector2f pos, std::function<void(void)> action, const std::string &text)
    : DrawableObject(ResourceManager::get().getTexture("Button.png"), pos)
    , m_action{ std::move(action) }
{
  m_text.setOutlineThickness(2);
  m_text.setFont(ResourceManager::get().getFont());
  m_text.setString(text);
  //while(sprite.getGlobalBounds().width < m_text.getGlobalBounds().width)
  //  m_text.setCharacterSize(m_text.getCharacterSize() - 1);
  m_text.setPosition(pos.x - m_text.getGlobalBounds().width / 2, pos.y - m_text.getGlobalBounds().height / 1.5f);
  m_text.setFillColor(sf::Color::White);
  m_text.setOutlineColor(sf::Color::Black);
}

void Button::draw(sf::RenderWindow &window)
{
  DrawableObject::draw(window);
  window.draw(m_text);
}

void Button::setTexture(sf::Texture &tex)
{
  sprite.setTexture(tex);
  sprite.setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f);
  sprite.setTextureRect(sf::Rect<int>(0, 0, tex.getSize().x, tex.getSize().y));
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
      m_text.setCharacterSize(35);
      m_text.setPosition(sprite.getPosition().x - m_text.getGlobalBounds().width / 2,
                         sprite.getPosition().y - m_text.getGlobalBounds().height / 1.5f);
      if(m_onHoverStart)
        m_onHoverStart(*this);
    }
    else
    {
      sprite.setScale(1, 1);
      m_text.setCharacterSize(30);
      m_text.setPosition(sprite.getPosition().x - m_text.getGlobalBounds().width / 2,
                         sprite.getPosition().y - m_text.getGlobalBounds().height / 1.5f);
      if(m_onHoverExit)
        m_onHoverExit(*this);
    }
  }
  if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Button::Left)
  {
    if(sprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
      m_action();
      ret = true;
    }
    
    if(sprite.getColor() != sf::Color::Transparent)
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

void Button::listenToOnHoverEnd(Button::tHoverCallBack cb)
{
  m_onHoverExit = std::move(cb);
}

void Button::listenToOnHoverStart(Button::tHoverCallBack cb)
{
  m_onHoverStart = std::move(cb);
}
