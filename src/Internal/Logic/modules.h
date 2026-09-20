#pragma once

#include <Shared/Reflection/ReflectableClass.h>
#include <Shared/strop.h>
#include <cstdint>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

struct PatchElement {
  std::vector<uint8_t> enableInstruction;
  std::vector<uint8_t> disableInstruction;

  PatchElement(const char *enableInstruction, const char *disableInstruction,
               uint32_t virtualAddr = 0x0);

  PatchElement(const char *enableInstruction,
               std::vector<uint8_t> disableInstruction,
               uint32_t virtualAddr = 0x0);

  PatchElement(std::vector<uint8_t> enableInstruction,
               const char *disableInstruction, uint32_t virtualAddr = 0x0);

  PatchElement(std::vector<uint8_t> enableInstruction,
               std::vector<uint8_t> disableInstruction,
               uint32_t virtualAddr = 0x0);

  PatchElement(void *targetFunc, void *origFunc);
};

[[deprecated("Use DynamicBranchReplacementSingle() instead.")]] PatchElement
DynamicFunctionReplacement(void *func, const char *disableInstruction,
                           uint32_t address);

[[deprecated("Use DynamicBranchReplacementSingle() instead.")]] PatchElement
DynamicFunctionReplacementBL(void *func, void *originalfunc, uint32_t address);

enum class BranchType {
  BranchIfNotEqual,
  BranchIfEqual,
  BranchIfLessThan,
  BranchIfGreaterThan,
  Branch,
  BranchLink
};

std::vector<uint8_t> DynamicBranchReplacementSingle(BranchType branchType,
                                                    void *func,
                                                    uint32_t address);

namespace Modules {
class Module : public Refl::Reflectable {
public:
  VABSTRACTCLASS(Modules::Module, ESC({nullptr}))

  virtual bool isCheatModule() = 0;

  virtual void enable() {
    this->m_enabled = true;
    this->onEnable();
  };
  virtual void disable() {
    this->m_enabled = false;
    this->onDisable();
  };

  virtual void onEnable(){};
  virtual void onDisable(){};

  virtual bool allowDisable() { return true; };

  virtual std::string helpText() { return {}; };

  const char *getModuleName() const;

  virtual std::vector<const char *> incompatibleModules() { return {}; };
  virtual std::vector<const char *> requiredModules() { return {}; };

  inline void toggle() { this->m_enabled ? this->disable() : this->enable(); }

  bool m_enabled = false;
};

/*
namespace TrampolineUtil {
	// srcAddress is the current instruction for proper branch distancing (fuck you PPC)
	std::array<unsigned char, 12> createBranchBytes(const uint32_t destAddress, const uint32_t srcAddress) {
		std::array<uint8_t, 4> branch = {
			// branch
			0x4b, 0xFF, 0xFF, 0xFF
		};

		uint32_t relativeAddress = destAddress - srcAddress;
		
		const size_t relativeAddressBytes = reinterpret_cast<size_t>(relativeAddress);
		std::memcpy(&branch[1], &relativeAddressBytes, sizeof(void *));

		return branch;
	}
}

struct TrampolinePatch {
	uint32_t address;
	void* archivedFunction;

	TrampolinePatch(void* const targetAddress, const size_t size);
};

TrampolinePatch(const void* srcFunction, const void* destFunction, const size_t size) {
	this->address = address;

	uint32_t srcFunctionAddress = (uint32_t) srcFunction;
	uint32_t destFunctionAddress = (uint32_t) destFunction;

    const auto branchBytes = TrampolineUtil::createBranchBytes(destAddress, srcFunctionAddress);
    
    const char* archivedFunction = new char [ size ];

    if (!archivedFunction) {
		CAFECRASH("Failed to create trampoline function for " + std::to_string(address));
		return;
    }

    std::memcpy(archivedFunction, srcFunctionAddress, size);
    std::memcpy(&reinterpret_cast<uint8_t*>(srcFunctionAddress, branchBytes.data(), branchBytes.size());

	this->archivedFunction = archivedFunction;
}
*/

class PatchModule : public Module {
// This access modifier will be changed to `private` in the future so you should not directly access the fields below and use the patch API functionality instead.
protected:
  VABSTRACTCLASS(Modules::PatchModule, ESC({&Module::classInfo, nullptr}))

  std::vector<std::tuple<uint32_t, PatchElement>> patch = {};
  //std::vector<std::tuple<uint32_t, void*>> trampolines = {};

public:
  void enable() override;
  void disable() override;

  void patchLine(uint32_t address, std::string instructionText);
  void patchLineBranch(uint32_t address, BranchType branchType, void* func);

  void apply();

  // to get rid of
  virtual void enablePatch() {
	  this->enable();
  }

  // to get rid of
  virtual void disablePatch() {
	  this->disable();
  }

  inline void toggle() {
    this->m_enabled ^= true;
    if (this->m_enabled)
      enable();
    else
      disable();
  }
};

class UpdateModule : public Module {
public:
  VABSTRACTCLASS(Modules::UpdateModule, ESC({&Module::classInfo, nullptr}))
  virtual void update(float deltaTime);

  virtual void render(float deltaTime);

  virtual bool requireRenderFocus() { return false; }

  void onEnable() override;
  void onDisable() override;

  virtual void start() {
  }
  virtual void stop() {
  }
};

struct ModuleState {
  ModuleState();

  void execModules(float deltaTime);

  std::vector<UpdateModule *> m_updateModules;
  std::vector<PatchModule *> m_patchModules;

  UpdateModule *getUpdateModule(const char *name);

  PatchModule *getPatchModule(const char *name);

  template <class T> T *getModule();

  void saveStates();

  bool isInFocusedModuleMode = false;
};
} // namespace Modules

#include "modules.inl"
