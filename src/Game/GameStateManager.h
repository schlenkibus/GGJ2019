#pragma once

#include "../Data/TenantData.h"

#include <vector>
#include <array>
#include <functional>
#include <memory>

class TenantData;

enum class ScreenState
{
  Start,
  NewTenant,
  KickTenant,
  DenyTenant,
  PlayerStats
};

class GameStateManager
{
 protected:
  GameStateManager();

 public:
  using TenantChangedCallback = std::function<void(std::shared_ptr<TenantData>)>;
  static GameStateManager& get();

  void setScreenState(ScreenState);

  void acceptTenant();
  void declineTenant();
  void kickTenant(TenantData* tenant);
  std::array<TenantData*, 3> getKickCandidates();
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

  void start();

 private:
  static constexpr const size_t maxAmountOfTenants = 10;
  const size_t monthlyExpenses = 5000;
  const size_t newTenantCost = 100;
  const size_t rentAmount = 1000;

  size_t nextDay();
  void generateNewTenant();
  void newTenantFee();
  void calculateWeek();

  void changeCurrentMoney(int amount);
  size_t calculateTenantPayment(std::shared_ptr<TenantData>);

  std::shared_ptr<TenantData> m_currentTenant;
  std::array<std::shared_ptr<TenantData>, maxAmountOfTenants> m_acceptedTenants{};
  std::vector<std::shared_ptr<TenantData>> m_declinedTenants{};
  std::vector<std::shared_ptr<TenantData>> m_thrownOutTenants{};

  TenantChangedCallback m_tenantChangedCallback;

  size_t m_days = 0;

  int m_currentMoneyEarned = 5000;
  int m_totalMoneyEarned = 0;
  int m_currentKarmaEarned = 0;
  int m_totalKarmaEarned = 0;
};
