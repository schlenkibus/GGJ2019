#include "Level.h"
#include "../Application.h"
#include "../tools/ResourceManager.h"
#include "../UI/Button.h"
#include <iostream>
#include "../UI/ChooseWindow.h"
#include "../Data/TenantData.h"
#include "../Data/TenantFactory.h"
#include "../tools/GameStateManager.h"
#include "../UI/GenericOkayWindowWithCallback.h"
#include "../UI/TenantView.h"

Level::Level() : firstUpdate {true}
{
  auto &rm = ResourceManager::get();
  auto &testTexture = rm.getTexture("test.png");

  setMenuScene();
}

void Level::start()
{
  ResourceManager::get().getMusic().play();

}

void Level::update(float delta)
{
    if (firstUpdate) {
      firstUpdate = false;
      auto &element = m_objects.front();
      auto refButton = dynamic_cast<Button*>(element.get());
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

  m_message = std::make_unique<ChooseWindow<DrawableObject>>(
      std::make_tuple(DrawableObject(rs.getTexture("faces/face1.png"), mid + sf::Vector2f(-400, 200),
                                     [=](sf::Event &e, DrawableObject &me) {
                                       if(clickedOnDrawable(e, me))
                                       {
                                         Application::get().getLevel().pushMessage("Selected Choice 1");
                                         return true;
                                       }
                                       return false;
                                     },
                                     nullptr),
                      DrawableObject(rs.getTexture("faces/face2.png"), mid + sf::Vector2f(-100, 200),
                                     [=](sf::Event &e, DrawableObject &me) {
                                       if(clickedOnDrawable(e, me))
                                       {
                                         Application::get().getLevel().pushMessage("Selected Choice 2");
                                         return true;
                                       }
                                       return false;
                                     },
                                     nullptr),
                      DrawableObject(rs.getTexture("faces/face3.png"), mid + sf::Vector2f(200, 200),
                                     [=](sf::Event &e, DrawableObject &me) {
                                       if(clickedOnDrawable(e, me))
                                       {
                                         Application::get().getLevel().pushMessage("Selected Choice 3");
                                         return true;
                                       }
                                       return false;
                                     },
                                     nullptr)));
}

void Level::pushTenant(TenantData &data)
{
  m_message = std::make_unique<TenantView>(data);
}

void Level::pushGenericMessage(std::string message, std::function<void(void)> okayAction)
{
  m_message = std::make_unique<GenericOkayWindowWithCallback>(message, "okay", std::move(okayAction));
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