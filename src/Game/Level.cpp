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
#include "../UI/GameStuff/Title.h"

Level::Level()
    : firstUpdate{ true }
{
  auto &rm = ResourceManager::get();
  auto &desk = rm.getTexture("Desk_try.png");
  auto &background = rm.getTexture("Background.png");

  m_desk = std::make_unique<DrawableObject>(desk, sf::Vector2f(0, 0));
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
  w.draw(m_cash);
  w.draw(m_dayCounter);

  for(auto &obj : m_objects)
  {
    obj->draw(w);
  }
  if(m_message)
    m_message->draw(w);
}

void Level::closeMessage()
{
  m_message.reset(nullptr);
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
  m_message = std::move(window);
}

void Level::setMenuScene()
{
  m_objects.clear();
  m_cash.setString("");
  m_dayCounter.setString("");
  Application::get().getLevel().closeMessage();

  m_objects.emplace_back(std::make_unique<Title>(Application::get().getMidPoint() + sf::Vector2f(0, -200), "unBEARable choices"));

  m_objects.emplace_back(
      std::make_unique<DrawableObject>(ResourceManager::get().getTexture("decals_images.png"), sf::Vector2f(670, 400)));

  m_objects.emplace_back(std::make_unique<Button>(sf::Vector2f(600, 325),
                                                  [&]() {
                                                    m_objects.clear();
                                                    GameStateManager::get().start();
                                                  },
                                                  "Start"));
}

void Level::setGameScene()
{
  m_objects.clear();

  auto &rm = ResourceManager::get();
  auto &exitTexture = rm.getTexture("exitbutton.png");

  m_objects.emplace_back(std::make_unique<Button>(sf::Vector2f(35, 35),
                                                  [&]() {
                                                    m_objects.clear();
                                                    m_cash.setString("");
                                                    m_dayCounter.setString("");
                                                    Application::get().getLevel().closeMessage();
                                                    Application::get().getLevel().setMenuScene();
                                                  },
                                                  ""));

  GameStateManager::get().init();
  m_cash.setPosition(1200 - m_cash.getGlobalBounds().width, 0);
  m_cash.setCash(GameStateManager::get().getCurrentMoney());

  auto &element = m_objects.front();
  auto refButton = dynamic_cast<Button *>(element.get());
  refButton->setTexture(exitTexture);
}
