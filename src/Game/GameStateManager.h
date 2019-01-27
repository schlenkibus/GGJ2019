#pragma once

#include "../Data/TenantData.h"

#include <vector>
#include <array>
#include <functional>
#include <memory>
#include <string>

class TenantData;

enum class ScreenState
{
  Start,
  NewTenant,
  KickTenant,
  KickTenantAfter,
  DenyTenant,
  PlayerStats,
  GameOver
};

class GameStateManager
{
 protected:
  GameStateManager();

 public:
  using TenantChangedCallback = std::function<void(std::shared_ptr<TenantData>)>;
  using MoneyChangedCallback = std::function<void(int)>;
  using DayChangedCallback = std::function<void(int)>;
  static GameStateManager& get();

  void init();

  void start();

  void setScreenState(ScreenState);

  void acceptTenant();
  void declineTenant();
  void kickTenant(TenantData* tenant);
  std::array<TenantData*, 3> getKickCandidates();
  void listenForTenantChanged(TenantChangedCallback);
  void listenForMoneyChange(MoneyChangedCallback);
  void listenForDayChange(DayChangedCallback);

  std::string getGameOverMessage();
  std::string getWeeklyReport();
  std::shared_ptr<TenantData> getTenant();
  std::shared_ptr<TenantData> getKickedTenant();
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
  static constexpr const size_t maxAmountOfTenants = 10;
  std::array<std::shared_ptr<TenantData>, maxAmountOfTenants> getCopyOfCurrentTenant()
  {
    return m_acceptedTenants;
  };
  int getNetIncome()
  {
    return m_netIncome;
  };

 private:
  const size_t monthlyExpenses = 5000;
  const size_t newTenantCost = 100;
  const size_t rentAmount = 1000;

  size_t nextDay();
  void generateNewTenant();
  void newTenantFee();
  void calculateWeek();

  void setMoney(int amount);
  void changeCurrentMoney(int amount);
  size_t calculateTenantPayment(std::shared_ptr<TenantData>);

  std::shared_ptr<TenantData> m_currentTenant;
  std::array<std::shared_ptr<TenantData>, maxAmountOfTenants> m_acceptedTenants{};
  std::vector<std::shared_ptr<TenantData>> m_declinedTenants{};
  std::vector<std::shared_ptr<TenantData>> m_thrownOutTenants{};

  MoneyChangedCallback m_moneyChanged;
  TenantChangedCallback m_tenantChangedCallback;
  DayChangedCallback m_dayChangedCallback;

  size_t m_days = 0;
  size_t lastCalculatedDay = 0;

  int m_currentMoneyEarned = 5000;
  int m_totalMoneyEarned = 0;
  int m_currentKarmaEarned = 0;
  int m_totalKarmaEarned = 0;

  // Weekly roundup data
  int m_netIncome = 0;
  int m_lifesDestroyed = 0;
  size_t m_tenantsKickedOut = 0;
};
