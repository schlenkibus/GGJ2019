#pragma once

#include "../UI/DrawableObject.h"
#include "../UI/YesNoMessage.h"
#include "../Data/TenantData.h"
#include "../UI/GenericWindow.h"
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
  void pushMessage(const std::string &message);
  void pushYesNoMessage(const std::string &message, YesNoMessage::tAction yes, YesNoMessage::tAction no);
  void closeMessage();
  void testChoose();
  void pushTenant(TenantData &data);
  void pushGenericMessage(std::string message, std::function<void(void)> okayAction);

 protected:
  std::vector<std::unique_ptr<DrawableObject>> m_objects;
  std::unique_ptr<GenericWindow> m_message;
  bool firstUpdate;
};
