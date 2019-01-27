#include "TenantKickEntry.h"
#include "../../Application.h"
#include "../../Game/GameStateManager.h"
#include "../../Data/TenantFactory.h"
#include "../../tools/ResourceManager.h"
#include "../../tools/AudioOneShotEngine.h"

TenantKickEntry::TenantKickEntry(TenantData *data, sf::Vector2f pos)
    : DrawableObject{ (data != nullptr ? data->getTexture() : TenantFactory::getTenant().getTexture()), pos }
    , info{ data }
    , kick{ pos + sf::Vector2f(0, 50),
            [&]() {
              GameStateManager::get().kickTenant(info);
              GameStateManager::get().setScreenState(ScreenState::KickTenantAfter);
            },
            "" }
{
  kick.setTexture(ResourceManager::get().getTexture("evictOverlay.png"));

  kick.sprite.setColor(sf::Color::Transparent);

  kick.listenToOnHoverStart([](Button& b){
      b.sprite.setColor(sf::Color::White);
  });

  kick.listenToOnHoverEnd([](Button& b){
    b.sprite.setColor(sf::Color::Transparent);
  });

  auto proto = TenantFactory::getTenant();
  if(data == nullptr)
    data = &proto;

  text.setPosition(pos + sf::Vector2f(-80, -175));
  text.setString(data->getStats());
  text.setFont(ResourceManager::get().getFont());
  text.setCharacterSize(30);
  text.setOutlineColor(sf::Color::Black);
  text.setOutlineThickness(1.2);
}

void TenantKickEntry::draw(sf::RenderWindow &window)
{
  DrawableObject::draw(window);
  kick.draw(window);
  window.draw(text);
}

bool TenantKickEntry::onEvent(sf::Event &e)
{
  if(kick.onEvent(e)) {
    return true;
  }

  return DrawableObject::onEvent(e);
}
