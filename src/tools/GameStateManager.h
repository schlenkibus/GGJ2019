#pragma once

#include "../Data/TenantData.h"

#include <vector>
#include <functional>
#include <memory>

class TenantData;

class GameStateManager
{
 public:
  using TenantChangedCallback = std::function<void(std::shared_ptr<TenantData>)>;
  static GameStateManager &get();

  void acceptTenant();
  void declineTenant();

  void listenForTenantChanged(TenantChangedCallback);
  std::shared_ptr<TenantData> getTenant();
  size_t getDay()
  {
    return m_days;
  };
  int getCurrentMoney()
  {
    return m_currentMoneyEarned;
  };
  int getCurrentkarma()
  {
    return m_currentKarmaEarned;
  };

  int getTotalMoneyEarn()
  {
    return m_totalMoneyEarned;
  };
  int getTotalkarmaEarn()
  {
    return m_totalKarmaEarned;
  };

 private:
  const size_t newTenantCost = 100;

  void nextDay();
  void generateNewTenant();
  void newTenantFee();

  void changeCurrentMoney(int amount);

  std::shared_ptr<TenantData> m_currentTenant;
  std::vector<std::shared_ptr<TenantData>> m_acceptedTenants{};
  std::vector<std::shared_ptr<TenantData>> m_declinedTenants{};
  std::vector<std::shared_ptr<TenantData>> m_thrownOutTenants{};

  TenantChangedCallback m_tenantChangedCallback;

  size_t m_days = 0;

  int m_currentMoneyEarned = 0;
  int m_totalMoneyEarned = 0;

  int m_currentKarmaEarned = 0;
  int m_totalKarmaEarned = 0;
};
