#include <list>
#include <vector>

#include "modules.h"
#include "Modules/fovchanger.h"
#include "Shared/Core/Logging.h"
#include<Shared/Reflection/Registries.h>
#include "Game/Assembler/ppcAssembler.h"
#include "Internal/silverlight.h"
#include "Internal/Logic/cheatcheck.h"
#include "Internal/Menus/DirectoryMenu.h"
#include "Shared/CemuBind.h"
#include "patch.h"
#include <mutex>

constexpr uint32_t BRANCH_COPY_26BITS = 0x03FFFFFF;

PatchElement::PatchElement(const char *enableInstruction, const char *disableInstruction, uint32_t virtualAddr) {
    PPCAssemblerInOut enableInstruction_ctx = {};
    PPCAssemblerInOut disableInstruction_ctx = {};
    enableInstruction_ctx.virtualAddress = virtualAddr;
    enableInstruction_ctx.forceNoAlignment = true;
    disableInstruction_ctx.virtualAddress = virtualAddr;
    disableInstruction_ctx.forceNoAlignment = true;

    ppcAssembler_assembleSingleInstruction(enableInstruction, &enableInstruction_ctx);
    ppcAssembler_assembleSingleInstruction(disableInstruction, &disableInstruction_ctx);

    if (enableInstruction_ctx.errorMsg.length() != 0) {
        CAFEINFO(enableInstruction_ctx.errorMsg)
    }

    CAFEASSERT(enableInstruction_ctx.errorMsg.length() == 0);
    if (disableInstruction_ctx.errorMsg.length() != 0) {
        CAFEINFO(disableInstruction_ctx.errorMsg)
    }
    CAFEASSERT(disableInstruction_ctx.errorMsg.length() == 0);

    this->enableInstruction = enableInstruction_ctx.outputData;
    this->disableInstruction = disableInstruction_ctx.outputData;
}

PatchElement::PatchElement(const char *enableInstruction, std::vector<uint8_t> disableInstruction,
                           uint32_t virtualAddr) {
    PPCAssemblerInOut enableInstruction_ctx = {};
    enableInstruction_ctx.virtualAddress = virtualAddr;
    enableInstruction_ctx.forceNoAlignment = true;

    ppcAssembler_assembleSingleInstruction(enableInstruction, &enableInstruction_ctx);

    if (enableInstruction_ctx.errorMsg.length() != 0) {
        CAFEINFO(enableInstruction_ctx.errorMsg)
    }
    CAFEASSERT(enableInstruction_ctx.errorMsg.length() == 0);

    this->enableInstruction = enableInstruction_ctx.outputData;
    this->disableInstruction = std::move(disableInstruction);
}

PatchElement::PatchElement(std::vector<uint8_t> enableInstruction, const char *disableInstruction,
                           uint32_t virtualAddr) {
    PPCAssemblerInOut disableInstruction_ctx = {};
    disableInstruction_ctx.virtualAddress = virtualAddr;
    disableInstruction_ctx.forceNoAlignment = true;

    ppcAssembler_assembleSingleInstruction(disableInstruction, &disableInstruction_ctx);

    if (disableInstruction_ctx.errorMsg.length() != 0) {
        CAFEINFO(disableInstruction_ctx.errorMsg)
    }
    CAFEASSERT(disableInstruction_ctx.errorMsg.length() == 0);

    this->disableInstruction = disableInstruction_ctx.outputData;
    this->enableInstruction = std::move(enableInstruction);
}

PatchElement::PatchElement(std::vector<uint8_t> enableInstruction, std::vector<uint8_t> disableInstruction,
                           uint32_t virtualAddr) {
    this->enableInstruction = std::move(enableInstruction);
    this->disableInstruction = std::move(disableInstruction);
}

std::vector<uint8_t> uint32_to_bytes(void* func) {
	uint32_t value = (uint32_t)func;

    std::vector<uint8_t> bytes(4); // Allocate space for 4 bytes
    bytes[0] = static_cast<uint8_t>((value >> 24) & 0xFF);
    bytes[1] = static_cast<uint8_t>((value >> 16) & 0xFF);
    bytes[2] = static_cast<uint8_t>((value >> 8) & 0xFF);
    bytes[3] = static_cast<uint8_t>(value & 0xFF);
    return bytes;
}

// vtable repl
PatchElement::PatchElement(void* func, void* origFunc) {
	this->enableInstruction = uint32_to_bytes(func);
	this->disableInstruction = uint32_to_bytes(origFunc);
}

namespace Modules {
    VREGISTRY(UpdateModule)
    VREGISTRY(PatchModule)

    const char *Module::getModuleName() const {
        return getClassInfo().m_name;
    }

    ModuleState::ModuleState() {
        g_UpdateModuleRegistry.collectObjects();

        m_updateModules = std::vector<UpdateModule *>(g_UpdateModuleRegistry.size());
        for (unsigned int i = 0; i < g_UpdateModuleRegistry.size(); i++) {
            m_updateModules[i] = (UpdateModule *) g_UpdateModuleRegistry.m_matchedClasses[i]->construct();
        }

        g_UpdateModuleRegistry.m_matchedClasses.clear();

        g_PatchModuleRegistry.collectObjects();

        m_patchModules = std::vector<PatchModule *>(g_PatchModuleRegistry.size());
        for (unsigned int i = 0; i < g_PatchModuleRegistry.size(); i++) {
            m_patchModules[i] = (PatchModule *) g_PatchModuleRegistry.m_matchedClasses[i]->construct();
        }
        g_PatchModuleRegistry.m_matchedClasses.clear();
    }

    void UpdateModule::update(float deltaTime) {}

    void UpdateModule::render(float deltaTime) {}

    void ModuleState::execModules(float deltaTime) {
        CHEAT_CHECK

		std::vector<Module*> allModules = {};

        for (const auto &module: m_updateModules) {
			Module* castedModule = dynamic_cast<Module*>(module);
			if (!castedModule) continue;
			allModules.push_back(castedModule);
		}

        for (const auto &module: m_patchModules) {
			Module* castedModule = dynamic_cast<Module*>(module);
			if (!castedModule) continue;
			allModules.push_back(castedModule);
		}

		std::vector<const char*> allIncompatibleModules = {};
		std::vector<const char*> allRequiredModules = {};

        for (const auto &module: allModules) {
            if (!module->m_enabled) continue;

			std::vector<const char*> incompatibleModules = module->incompatibleModules();
			std::vector<const char*> requiredModules = module->requiredModules();

			for (const auto& incompatibleModule : incompatibleModules) {
				allIncompatibleModules.push_back(incompatibleModule);
			}
			for (const auto& requiredModule : requiredModules) {
				allRequiredModules.push_back(requiredModule);
			}
        }

		for (const auto& moduleStr : allIncompatibleModules) {
			UpdateModule* updateModule = this->getUpdateModule(moduleStr);
			if (updateModule) {
				updateModule->disable();
				continue;
			}

			PatchModule* patchModule = this->getPatchModule(moduleStr);
			if (patchModule) {
				// Check before disabling to prevent unnecessary cache invalidation.
				if (patchModule->m_enabled) {
					patchModule->disable();
				}
				continue;
			}

			std::string formattedModuleStr(moduleStr);
			CAFECRASH("Module with the name \"" + formattedModuleStr + "\" not found when searching incompatible modules.");
		}

		for (const auto& moduleStr : allRequiredModules) {
			UpdateModule* updateModule = this->getUpdateModule(moduleStr);
			if (updateModule) {
				updateModule->enable();
				continue;
			}

			PatchModule* patchModule = this->getPatchModule(moduleStr);
			if (patchModule) {
				if (!patchModule->m_enabled) {
					patchModule->enable();
				}
				continue;
			}

			std::string formattedModuleStr(moduleStr);
			CAFECRASH("Module with the name \"" + formattedModuleStr + "\" not found when searching required modules.");
		}

		bool focusRequired = false;

		for (const auto &module : m_updateModules) {
			if (!module->m_enabled) continue;
			if (module->requireRenderFocus() && !focusRequired) {
				module->render(deltaTime);
				focusRequired = true;
				break;
			}
		}

		this->isInFocusedModuleMode = focusRequired;

		for (const auto &module : m_updateModules) {
			if (!module->m_enabled) continue;
			if (!focusRequired) module->render(deltaTime);
			module->update(deltaTime);
		}
    }

    UpdateModule *ModuleState::getUpdateModule(const char *name) {
        auto iter = std::ranges::find_if(m_updateModules, [&](const UpdateModule *module) {
            return module->getModuleName() == name;
        });
        if (iter == m_updateModules.end()) {
            //CAFECRASH("Unable to find module: " + std::string(name))
			return nullptr;
        }

        return *iter;
    }

    PatchModule *ModuleState::getPatchModule(const char *name) {
        auto iter = std::ranges::find_if(m_patchModules, [&](const PatchModule *module) {
            return module->getModuleName() == name;
        });
        if (iter == m_patchModules.end()) {
            //CAFECRASH("Unable to find module: " + std::string(name))
	    		return nullptr;
        }

        return *iter;
    }

    void ModuleState::saveStates() {

    }


	void PatchModule::enable() {
		this->m_enabled = true;


    for (auto const &patchNode: this->patch) {
      uint32_t location = get<0>(patchNode);
      PatchElement patchElement = get<1>(patchNode);

      if(location & 0x02000000){
        location -= 0x02000000;
      }
      
      std::call_once(initialized_rpl_pointers, init_rpl_pointers);

      location += (uint32_t)text_section;      

      memcpy((void *) location, static_cast<void *>(patchElement.enableInstruction.data()), 4);

      SLInvalidateCache(location, location + 4);
    }

		this->onEnable();
  }

    void PatchModule::disable() {
		if (!this->allowDisable()) return;

		this->m_enabled = false;

        for (auto const &patchNode: this->patch) {
            uint32_t location = get<0>(patchNode);
            PatchElement patchElement = get<1>(patchNode);

            memcpy((void *) location, static_cast<void *>(patchElement.disableInstruction.data()), 4);

            SLInvalidateCache(location, location + 4);
        }

		this->onDisable();
    }

    void PatchModule::apply() {
        if (this->m_enabled) {
            enable();
        } else {
            disable();
        }
    }

	void PatchModule::patchLine(uint32_t address, std::string instructionText) {
		std::string moduleName = this->getModuleName();

		if (address < 0x02000000) {
			CAFECRASH("Module \"" + moduleName + "\" passed an invalid address \"" + std::to_string(address) + "\" in patchLine().");
		}

		std::string branchInstructions[] = {"bl", "b", "beq", "bne", "bne", "bge"};

		for (const auto& branchInstruction : branchInstructions) {
			if (instructionText.rfind(branchInstruction + " ") == 0) {
				CAFECRASH("Module \"" + moduleName + "\" passed a branch instruction in `patchLine()`. Please use `patchLineBranch` instead for patches with branches.");
			}
		}

		const auto origBytesAddr = reinterpret_cast<uint32_t*>(address);
		const auto origBytes = *origBytesAddr;
		std::vector<std::uint8_t> origBytesVec( (std::uint8_t*)&origBytes, (std::uint8_t*)&(origBytes) + sizeof(std::uint32_t) );

		this->patch.push_back(
			{ address, PatchElement(instructionText.c_str(), origBytesVec) }
		);
	}

	void PatchModule::patchLineBranch(uint32_t address, BranchType branchType, void* func) {
		std::string branchTypeStr = {};

		switch (branchType) {
			case BranchType::BranchIfEqual:
				branchTypeStr = "beq";
				break;
				case BranchType::BranchIfNotEqual:
					branchTypeStr = "bne";
					break;
				case BranchType::Branch:
					branchTypeStr = "b";
					break;
				case BranchType::BranchLink:
					branchTypeStr = "bl";
					break;
				case BranchType::BranchIfLessThan:
					branchTypeStr = "blt";
					break;
				case BranchType::BranchIfGreaterThan:
					branchTypeStr = "bgt";
					break;
				default:
					branchTypeStr = "b";
		}

		std::string text = branchTypeStr + " 0x0" + toHexString((uint32_t) func);

		PPCAssemblerInOut instruction_ctx = {};
		instruction_ctx.virtualAddress = address;
		instruction_ctx.forceNoAlignment = true;

		ppcAssembler_assembleSingleInstruction(text.c_str(), &instruction_ctx);

		if (instruction_ctx.errorMsg.length() != 0) {
			CAFEINFO(instruction_ctx.errorMsg)
		}

		CAFEASSERT(instruction_ctx.errorMsg.length() == 0);

		std::vector<uint8_t> instruction = instruction_ctx.outputData;

		uint32_t &dat = *(uint32_t *) instruction.data();
		uint32_t relativeFunc = (uint32_t) func - address;
		dat |= relativeFunc & BRANCH_COPY_26BITS;

		const auto origBytesAddr = reinterpret_cast<uint32_t*>(address);
		const auto origBytes = *origBytesAddr;
		std::vector<std::uint8_t> origBytesVec( (std::uint8_t*)&origBytes, (std::uint8_t*)&(origBytes) + sizeof(std::uint32_t) );

		this->patch.push_back(
			{ address, PatchElement(instruction, origBytesVec) }
		);
	}

    REGISTERABSTRACTVCLASS(Module)

    REGISTERABSTRACTVCLASS(UpdateModule)

    REGISTERABSTRACTVCLASS(PatchModule)
}

// Do NOT use this function inside modules anymore. Please use `patchLineBranch()` with branch type set to `BranchType::BranchLink` instead as this function will be removed in the future.
PatchElement DynamicFunctionReplacementBL(void *func, void *originalfunc, uint32_t address) {
    std::string enabledText = "bl 0x0" + toHexString((uint32_t) func);
    std::string disableText = "bl 0x0" + toHexString((uint32_t) originalfunc);

    auto patch = PatchElement(enabledText.c_str(), disableText.c_str(), address);

    //Fix the assembler not generating correct jumps manually
    uint32_t &dat = *(uint32_t *) patch.enableInstruction.data();
    uint32_t relativeFunc = (uint32_t) func - address;
    dat |= relativeFunc & BRANCH_COPY_26BITS;

    uint32_t &datOrig = *(uint32_t *) patch.disableInstruction.data();
    uint32_t relativeFuncOrig = (uint32_t) originalfunc - address;
    datOrig |= relativeFuncOrig & BRANCH_COPY_26BITS;

    return patch;
}

// Do NOT use this function inside modules anymore. Please use `patchLineBranch()` instead as this function will be removed in the future.
std::vector<uint8_t> DynamicBranchReplacementSingle(BranchType branchType, void *func, uint32_t address) {
    std::string branchTypeStr = {};

    switch (branchType) {
        case BranchType::BranchIfEqual:
            branchTypeStr = "beq";
            break;
        case BranchType::BranchIfNotEqual:
            branchTypeStr = "bne";
            break;
        case BranchType::Branch:
            branchTypeStr = "b";
            break;
        case BranchType::BranchLink:
            branchTypeStr = "bl";
            break;
        case BranchType::BranchIfLessThan:
            branchTypeStr = "blt";
            break;
        case BranchType::BranchIfGreaterThan:
            branchTypeStr = "bgt";
            break;
        default:
            branchTypeStr = "b";
    }

    std::string text = branchTypeStr + " 0x0" + toHexString((uint32_t) func);

    PPCAssemblerInOut instruction_ctx = {};
    instruction_ctx.virtualAddress = address;
    instruction_ctx.forceNoAlignment = true;

    ppcAssembler_assembleSingleInstruction(text.c_str(), &instruction_ctx);

    if (instruction_ctx.errorMsg.length() != 0) {
        CAFEINFO(instruction_ctx.errorMsg)
    }

    CAFEASSERT(instruction_ctx.errorMsg.length() == 0);

    std::vector<uint8_t> instruction = instruction_ctx.outputData;

    uint32_t &dat = *(uint32_t *) instruction.data();
    uint32_t relativeFunc = (uint32_t) func - address;
    dat |= relativeFunc & BRANCH_COPY_26BITS;

    return instruction;
}

// Do NOT use this function inside modules anymore. Please use `patchLineBranch()` instead as this function will be removed in the future.
PatchElement DynamicFunctionReplacement(void *func, const char *disableInstruction, uint32_t address) {

    static std::string enabledText = "b 0x0" + toHexString((uint32_t) func);
    static std::string disableText = disableInstruction;

    auto patch = PatchElement(enabledText.c_str(), disableText.c_str(), address);

    //Fix the assembler not generating correct jumps manually
    uint32_t &dat = *(uint32_t *) patch.enableInstruction.data();
    uint32_t relativeFunc = (uint32_t) func - address;
    dat |= relativeFunc & BRANCH_COPY_26BITS;

    return patch;
}

namespace Modules {
	// Temporary until I give a shit to replace the deprecated functions `start()` and `stop()`.
	void UpdateModule::onEnable() {
		this->start();
	}
	void UpdateModule::onDisable() {
		this->stop();
	}
}
