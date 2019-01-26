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
  auto &testTexture = rm.getTexture("test.png");

  m_objects.emplace_back(std::make_unique<Button>(sf::Vector2f(600, 325),
                                                  [&]() {
                                                    m_objects.clear();
                                                    GameStateManager::get().start();
                                                  },
                                                  "Start"));

  /*m_objects.emplace_back(std::make_unique<Button>(sf::Vector2f(300, 300),
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
  */
}

void Level::start()
{
  ResourceManager::get().getMusic().play();
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
