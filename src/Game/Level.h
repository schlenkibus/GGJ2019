#pragma once

#include "../UI/generic/DrawableObject.h"
#include "../UI/generic/YesNoMessage.h"
#include "../Data/TenantData.h"
#include "../UI/generic/GenericWindow.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Level
{
 public:
  Level();
  void start();
  void update(float delta);
  void onEvent(sf::Event &e);
  void draw(sf::RenderWindow &w);
  void closeMessage();
  void pushTenant(TenantData &data);
  void pushGenericMessage(std::string message, std::function<void(void)> okayAction);
  void install(std::unique_ptr<GenericWindow> &&window);
  void setGameScene();
  void setMenuScene();

 protected:
  std::vector<std::unique_ptr<DrawableObject>> m_objects;
  std::unique_ptr<GenericWindow> m_message;
  bool firstUpdate;
    std::unique_ptr<DrawableObject> m_desk;
  std::unique_ptr<DrawableObject> m_background;
};
