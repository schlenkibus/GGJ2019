#include "TenantOverview.h"
#include "../../Application.h"
#include "../../Game/GameStateManager.h"
#include "../../Data/TenantFactory.h"
#include "../../tools/ResourceManager.h"

TenantOverview::TenantOverview(TenantData *data, sf::Vector2f pos)
        : DrawableObject{ (data != nullptr ? data->getTexture() : TenantFactory::getTenant().getTexture()), pos }
        , info{ data }
{
    text.setPosition(pos + sf::Vector2f(43, -10));
    text.setString(data->getStats());
    text.setFont(ResourceManager::get().getFont());
    text.setCharacterSize(30);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1.2);
}

void TenantOverview::draw(sf::RenderWindow &window)
{
    DrawableObject::draw(window);
    window.draw(text);
}

bool TenantOverview::onEvent(sf::Event &e)
{
    return DrawableObject::onEvent(e);
}
