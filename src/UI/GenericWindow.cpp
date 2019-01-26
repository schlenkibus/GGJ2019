
#include "GenericWindow.h"
#include "../Application.h"
#include "../tools/ResourceManager.h"

GenericWindow::GenericWindow(const std::string &message, const std::string &header, sf::Texture &tex)
    : DrawableObject(tex, Application::get().getMidPoint())
    , m_header{ header, ResourceManager::get().getFont() }
    , m_message{ message, ResourceManager::get().getFont() }
{

  std::string perm;
  auto lastInsertAgo = 0;

  for(auto c : message)
  {
    if(std::isspace(c))
    {
      if(lastInsertAgo >= 15)
      {
        perm += '\n';
        lastInsertAgo = 0;
        continue;
      }
    }
    perm += c;
    lastInsertAgo++;
  }

  m_message.setString(perm);

  m_header.setPosition(Application::get().getMidPoint() + sf::Vector2f(-135, -250));
  m_message.setPosition(Application::get().getMidPoint() + sf::Vector2f(-135, -200));
  m_message.setOutlineThickness(1.5);
  m_message.setOutlineColor(sf::Color::Black);
  m_message.setFillColor(sf::Color::White);
}

void GenericWindow::draw(sf::RenderWindow &window)
{
  DrawableObject::draw(window);
  window.draw(m_header);
  window.draw(m_message);
}

bool GenericWindow::onEvent(sf::Event &e)
{
  return false;
}
