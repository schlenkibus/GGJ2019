#pragma once

#include "DataManager.h"
#include <string>

class TenantData
{
 public:
  TenantData() = default;
  std::string toString() const;
 protected:
  std::string name;
  std::string profession;
  int age{};
  int factor{};
  std::string reccomendation;
  std::string outcome;
  int salary{};

  friend class TenantFactory;
};
