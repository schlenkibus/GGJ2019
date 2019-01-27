#include <sstream>
#include "GenericWindow.h"
#include "../../Application.h"
#include "../../tools/ResourceManager.h"

GenericWindow::GenericWindow(const std::string &message, const std::string &header, sf::Texture &tex)
    : DrawableObject(tex, Application::get().getMidPoint())
    , m_header{ header, ResourceManager::get().getFont() }
    , m_message{ message, ResourceManager::get().getFont() }
{

  auto splitStringOnAnyDelimiter = [](const std::string &s, char delimiter) -> std::vector<std::string> {
    std::vector<std::string> strings;
    std::string token;
    std::istringstream tokenStream(s);
    while(std::getline(tokenStream, token, delimiter))
    {
      std::string o{};
      for(auto &c : token)
      {
        o += c;
      }

      if(*o.end() != ' ')
        o += " ";

      if(!o.empty())
        strings.push_back(o);
    }
    return strings;
  };

  m_message.setCharacterSize(20);
  scale(1.25);
  std::string perm;

  auto messageWords = splitStringOnAnyDelimiter(message, ' ');

  sf::Text testText(m_message);

  for(const auto &word : messageWords)
  {
    testText.setString(perm + " " + word);
    if(testText.getGlobalBounds().width > sprite.getGlobalBounds().width * 0.7)
    {
      perm += "\n";
      perm += word;
    }
    else
    {
      perm += word;
    }
  }

  m_message.setString(perm);

  m_header.setPosition(Application::get().getMidPoint() + sf::Vector2f(-135, -250));
  m_message.setPosition(Application::get().getMidPoint() + sf::Vector2f(-135, -200));

  m_header.setOutlineThickness(1.5);
  m_header.setOutlineColor(sf::Color::White);
  m_header.setFillColor(sf::Color::Black);
  m_message.setOutlineThickness(1.5);
  m_message.setOutlineColor(sf::Color::White);
  m_message.setFillColor(sf::Color::Black);
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

const size_t GenericWindow::charactersToNewLine()
{
  return static_cast<const size_t>(sprite.getGlobalBounds().width / 20);
}
