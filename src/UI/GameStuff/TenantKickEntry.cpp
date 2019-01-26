#include "TenantKickEntry.h"
#include "../../Application.h"
#include "../../Game/GameStateManager.h"
#include "../../Data/TenantFactory.h"

TenantKickEntry::TenantKickEntry(TenantData *data, sf::Vector2f pos)
    : DrawableObject{ (data != nullptr ? data->getTexture() : TenantFactory::getTenant().getTexture()), pos }
    , info{ data }
    , kick{ pos + sf::Vector2f(0, 250), [&]() { GameStateManager::get().kickTenant(data); }, "Throw Out!" }
{
  auto proto = TenantFactory::getTenant();
  if(data == nullptr)
    data = &proto;

  text.setPosition(pos - sf::Vector2f(0, -250));
    text.setString(data->getStats());
  text.setFont(ResourceManager::get().getFont());
}

void TenantKickEntry::draw(sf::RenderWindow &window)
{
  DrawableObject::draw(window);
  kick.draw(window);
  window.draw(text);
}

bool TenantKickEntry::onEvent(sf::Event &e)
{
  if(kick.onEvent(e))
    return true;

  return DrawableObject::onEvent(e);
}