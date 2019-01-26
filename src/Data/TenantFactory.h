#pragma once

#include <sstream>
#include "TenantData.h"

class TenantFactory
{
 public:
  static TenantData getTenant();
};