#pragma once

#include <sstream>
#include <memory>
#include "TenantData.h"

class TenantFactory : public std::enable_shared_from_this<TenantFactory>
{
 public:
  static TenantData getTenant();
};