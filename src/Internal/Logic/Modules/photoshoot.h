#pragma once

#include "Game/Cmn/PlayerInfo.h"
#include "InputModule.h"
#include "Internal/Logic/modules.h"

namespace Modules {
class PhotoshootCommandInput : public InputModule {
  VCLASS(PhotoshootCommandInput, ESC({&InputModule::classInfo, nullptr}))
public:
  PhotoshootCommandInput();

  bool isCheatModule() override;

  void receivedEntry(const std::u16string &input) override;

  std::string error = {};

  Cmn::PlayerInfo::PlayerInfo infos[8] = {};
  bool infosInitialized[8] = {false, false, false, false,
                              false, false, false, false};
};

class PhotoshootPatch : public PatchModule {
  VCLASS(PhotoshootPatch, ESC({&PatchModule::classInfo, nullptr}))
public:
  bool isCheatModule() override;

  PhotoshootPatch();
};

class PhotoshootUpdate : public UpdateModule {
  VCLASS(PhotoshootUpdate, ESC({&UpdateModule::classInfo, nullptr}))
public:
  void onEnable() override;

  void onDisable() override;

  bool isCheatModule() override;

  bool requireRenderFocus() override;

public:
  void update(float deltaTime) override;

  void render(float deltaTime) override;

  uint32_t selectedPlayerIdx = 0;
  bool renderingEnabled = true;
};

class PhotoshootWrapper : public UpdateModule {
  VCLASS(PhotoshootWrapper, ESC({&UpdateModule::classInfo, nullptr}))
public:
  void onEnable() override;

  void onDisable() override;

  bool isCheatModule() override;

public:
  void update(float deltaTime) override;

  std::vector<const char *> requiredModules() override;
  std::vector<const char *> incompatibleModules() override;
};
} // namespace Modules
