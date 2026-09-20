//
// Created by tv on 04.11.23.
//

#pragma once

#include "Internal/Logic/modules.h"

namespace Modules {
class NoAirChargePenalty : public PatchModule {
  VCLASS(NoAirChargePenalty, ESC({&PatchModule::classInfo, nullptr}))
public:
  bool isCheatModule() override;

  NoAirChargePenalty();
};
} // namespace Modules
