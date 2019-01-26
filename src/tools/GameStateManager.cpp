#include "GameStateManager.h"

#include "../Data/TenantFactory.h"
#include "../Application.h"
#include "../tools/AudioOneShotEngine.h"

GameStateManager &GameStateManager::get()
{
  static GameStateManager gameStateManager;
  return gameStateManager;
}

void GameStateManager::acceptTenant()
{

  AudioOneShotEngine::get().play("happyTenant.wav");
  if(!m_acceptedTenants.empty())
  {
    auto it = std::next(m_acceptedTenants.begin());

    std::move(m_acceptedTenants.begin(), std::next(m_acceptedTenants.begin()), std::back_inserter(m_thrownOutTenants));

    m_acceptedTenants.erase(m_acceptedTenants.begin());
  }

  m_acceptedTenants.push_back(m_currentTenant);
  newTenantFee();
  nextDay();
}

void GameStateManager::declineTenant()
{

  AudioOneShotEngine::get().play("sadTenant.wav");
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
  changeCurrentMoney(static_cast<int>(-newTenantCost));
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
