#include "GameStateManager.h"

#include "../Data/TenantFactory.h"
#include "../Application.h"

GameStateManager &GameStateManager::get()
{
  static GameStateManager gameStateManager;
  return gameStateManager;
}

void GameStateManager::acceptTenant()
{
  if(m_acceptedTenants.size() > 0)
  {
    auto it = std::next(m_acceptedTenants.begin());

    std::move(m_acceptedTenants.begin(), it, std::back_inserter(m_thrownOutTenants));

    m_acceptedTenants.erase(it);
  }

  m_acceptedTenants.push_back(m_currentTenant);
  newTenantFee();
  nextDay();
}

void GameStateManager::declineTenant()
{
  m_declinedTenants.push_back(m_currentTenant);
  nextDay();
}

void GameStateManager::nextDay()
{
  m_days++;
  generateNewTenant();
}

void GameStateManager::generateNewTenant()
{
  m_currentTenant = std::make_shared<TenantData>(TenantFactory::getTenant());
  if(m_tenantChangedCallback)
  {
    m_tenantChangedCallback(m_currentTenant);
  }
}

void GameStateManager::listenForTenantChanged(TenantChangedCallback function)
{
  m_tenantChangedCallback = std::move(function);
}

void GameStateManager::newTenantFee()
{
  changeCurrentMoney(-newTenantCost);
}

void GameStateManager::changeCurrentMoney(int amount)
{
  m_currentMoneyEarned += amount;
  if(amount > 0)
  {
    m_totalMoneyEarned += amount;
  }
}

std::shared_ptr<TenantData> GameStateManager::getTenant()
{
  return m_currentTenant;
}

void GameStateManager::start()
{
  listenForTenantChanged([](std::shared_ptr<TenantData> ptr) { Application::get().getLevel().pushTenant(*ptr.get()); });
  nextDay();
}
