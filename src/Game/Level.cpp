#include "Level.h"
#include "../Application.h"
#include "../tools/ResourceManager.h"
#include "../UI/generic/Button.h"
#include <iostream>
#include "../UI/GameStuff/TenantKickScreen.h"
#include "../Data/TenantData.h"
#include "../Data/TenantFactory.h"
#include "GameStateManager.h"
#include "../UI/generic/GenericOkayWindowWithCallback.h"
#include "../UI/GameStuff/TenantView.h"

Level::Level()
    : firstUpdate{ true }
{
  auto &rm = ResourceManager::get();
  auto &desk = rm.getTexture("Desk_try.png");
  auto &background = rm.getTexture("Background.png");

  m_desk = std::make_unique<DrawableObject>(desk, sf::Vector2f(0,0));
  m_background = std::make_unique<DrawableObject>(background, sf::Vector2f(0, 0));

}

void Level::start()
{
  ResourceManager::get().getMusic().play();

  m_background->setPos(Application::get().getMidPoint());
  m_desk->setPos(Application::get().getMidPoint());

  setMenuScene();
}

void Level::update(float delta)
{
  if(firstUpdate)
  {
    firstUpdate = false;
    auto &element = m_objects.front();
    auto refButton = dynamic_cast<Button *>(element.get());
    refButton->setPos(Application::get().getMidPoint());
  }
  for(auto &obj : m_objects)
  {
    obj->update(delta);
  }
  if(m_message)
    m_message->update(delta);
}

void Level::onEvent(sf::Event &e)
{
  if(m_message)
    if(m_message->onEvent(e))
      return;

  for(auto &obj : m_objects)
  {
    if(obj->onEvent(e))
      break;
  }
}

void Level::draw(sf::RenderWindow &w)
{

  m_background->draw(w);
  m_desk->draw(w);

  for(auto &obj : m_objects)
  {
    obj->draw(w);
  }
  if(m_message)
    m_message->draw(w);
}

void Level::pushMessage(const std::string &message)
{
  std::cout << message << std::endl;
}

void Level::closeMessage()
{
  m_message.reset(nullptr);
}

void Level::pushYesNoMessage(const std::string &message, YesNoMessage::tAction yes, YesNoMessage::tAction no)
{
  m_message = std::make_unique<YesNoMessage>(std::move(yes), std::move(no), message);
}

void Level::testChoose()
{
  auto &rs = ResourceManager::get();
  auto mid = Application::get().getMidPoint();

  auto clickedOnDrawable = [](sf::Event &e, DrawableObject &o) -> bool {
    return e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left
        && o.contains(Application::get().getMouse());
  };
}

void Level::pushTenant(TenantData &data)
{
  m_message = std::make_unique<TenantView>(data);
}

void Level::pushGenericMessage(std::string message, std::function<void(void)> okayAction)
{
  m_message = std::make_unique<GenericOkayWindowWithCallback>(message, "okay", std::move(okayAction));
}

void Level::install(std::unique_ptr<GenericWindow> &&window)
{
  m_message.reset(window.release());
}

void Level::setMenuScene() {
    m_objects.emplace_back(std::make_unique<Button>(sf::Vector2f(600, 325),
                                                    [&]() {
                                                        m_objects.clear();
                                                        GameStateManager::get().start();
                                                    },
                                                    "Start"));
}

void Level::setGameScene() {
  auto &rm = ResourceManager::get();
  auto &exitTexture = rm.getTexture("exitbutton.png");

  m_objects.emplace_back(std::make_unique<Button>(sf::Vector2f(100, 100),
                                                  [&]() {
                                                      m_objects.clear();
                                                      Application::get().getLevel().closeMessage();
                                                      Application::get().getLevel().setMenuScene();
                                                  },
                                                  ""));
  auto &element = m_objects.front();
  auto refButton = dynamic_cast<Button*>(element.get());
  refButton->setTexture(exitTexture);
}
