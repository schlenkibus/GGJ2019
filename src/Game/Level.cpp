#include "Level.h"
#include "../Application.h"
#include "../tools/ResourceManager.h"
#include "../UI/Button.h"
#include <iostream>
#include "../UI/ChooseWindow.h"

Level::Level()
{
  auto &rm = ResourceManager::get();
  auto &testTexture = rm.getTexture("test.png");

  m_objects.emplace_back(std::make_unique<Button>(sf::Vector2f(300, 400),
                                                  []() {
                                                    Application::get().getLevel().pushMessage(
                                                        "I'm just an annoying Message! I don't "
                                                        "care if this annoys you! :)");
                                                  },
                                                  "Test"));

  m_objects.emplace_back(std::make_unique<Button>(sf::Vector2f(300, 300),
                                                  []() { Application::get().getLevel().testChoose(); }, "Choose!"));

  m_objects.emplace_back(
      std::make_unique<Button>(sf::Vector2f(300, 500),
                               []() {
                                 Application::get().getLevel().pushYesNoMessage(
                                     "Do you realy want to do that? Are you absolutely sure this is "
                                     "neccessarry?? If so why? And Why do we exist in the first place. "
                                     "Do you Agree?",
                                     []() { Application::get().getLevel().pushMessage("Yes is a good Answer!"); },
                                     []() { Application::get().getLevel().pushMessage("No also is a good Answer!"); });
                               },
                               "Yes Or No?"));

  m_objects.emplace_back(std::make_unique<Button>(sf::Vector2f(300, 600), []() { Application::get().quit(); }, "Quit"));
  m_objects.emplace_back(
      std::make_unique<DrawableObject>(testTexture, sf::Vector2f(300, 100), nullptr,
                                       [](float delta, DrawableObject &o) { o.setPos(sf::Vector2f(delta, delta)); }));
}

void Level::update(float delta)
{
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
  m_message = std::make_unique<CommonMessageWindow>(message, "Common Message");
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