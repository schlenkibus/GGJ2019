#include "GameStateManager.h"

#include "../Data/TenantFactory.h"

GameStateManager &GameStateManager::get()
{
    static GameStateManager gameStateManager;
    return gameStateManager;
}

void GameStateManager::acceptTenant()
{
    m_acceptedTenants.push_back(m_currentTenant);
    payNewTenantFee();
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
    if (m_tenantChangedCallback)
    {
        m_tenantChangedCallback(m_currentTenant);
    }
}

void GameStateManager::listenForTenantChanged(TenantChangedCallback function)
{
    m_tenantChangedCallback = function;
}

void GameStateManager::newTenantFee()
{
    changeCurrentMoney(newTenantCost);
}

void GameStateManager::changeCurrentMoney(int amount)
{
    m_currentMoneyEarned += amount;
    if (amount > 0)
    {
        m_totalMoneyEarned += amount;
    }
}

std::shared_ptr<TenantData> GameStateManager::getTenant()
{
    return m_currentTenant;
}
