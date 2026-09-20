//
// Created by tv on 04.11.23.
//
#include"ipinspectionhook.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>
#include "Game/nn/nex/InetAddress.h"
#include "Shared/netop.h"
#include "Game/nn/pia/common/Socket.h"
#include "Game/Filetypes/Helpers/Filesystem.h"
#include <coreinit/filesystem.h>
#include "Game/nn/pia/session/Session.h"

//static FSFileHandle logFileHandle;

void addLogEntry(std::string funcName, std::string log) {
	std::string logEntry = "[ " + funcName + " ] " + log;

	CAFEINFO(logEntry);

	/*
	FSCmdBlock cmdBlock;

	std::vector<uint8_t> logBytes(logEntry.begin(), logEntry.end());
	uint8_t *logBytesData = logBytes.data();

    FSInitCmdBlock(&cmdBlock);
	FSWriteFile(&Filesystem::g_fsClient, &cmdBlock, logBytesData, logBytes.size(), 1, logFileHandle, 0x0, FS_ERROR_FLAG_ALL);
	*/
}

void repl_SetAddress(nn::nex::InetAddress::InetAddress* _this, uint32_t address) {
	addLogEntry("nn::nex::InetAddress::SetAddress()", "outgoing IP address: " + formatIpBytes(address));

	nn::nex::InetAddress::SetAddress(_this, address);
}

void repl_GetAddress(nn::nex::InetAddress::InetAddress* _this, uint32_t address, uint32_t unk) {
	addLogEntry("nn::nex::InetAddress::GetAddress()", "ingoing IP address: " + formatIpBytes(address));

	nn::nex::InetAddress::GetAddress(_this, address, unk);
}

void repl_GetBroadcastAddress(nn::nex::InetAddress::InetAddress* _this, uint32_t address, uint32_t unk) {
	addLogEntry("nn::nex::InetAddress::GetAddress()", "received IP address: " + formatIpBytes(address));

	nn::nex::InetAddress::GetAddress(_this, address, unk);
}

int32_t repl_SendTo(nn::pia::common::Socket::Socket* _this, int32_t param_1, int32_t param_2, nn::pia::common::InetAddress::InetAddress* ipAddress, int32_t* param_4) {
	addLogEntry("nn::pia::common::Socket::SendTo()", "outgoing IP address: " + formatIpBytes(ipAddress->address));

	return nn::pia::common::Socket::SendTo(_this, param_1, param_2, ipAddress, param_4);
}

int32_t repl_RecvFrom(nn::pia::common::Socket::Socket* _this, int32_t param_1, int32_t param_2, nn::pia::common::InetAddress::InetAddress* ipAddress, int32_t param_4, int32_t* param_5) {
	int32_t result = nn::pia::common::Socket::RecvFrom(_this, param_1, param_2, ipAddress, param_4, param_5);
	addLogEntry("nn::pia::common::Socket::RecvFrom()", "ingoing IP address: " + formatIpBytes(ipAddress->address));

	return result;
}

int32_t repl_GetSessionId(nn::pia::session::Session::Session* _this, int32_t* param_1) {
	int32_t sessionId = nn::pia::session::Session::GetSessionId(_this, param_1);

	addLogEntry("nn::pia::session::Session::GetSessionId()", "received session ID : " + std::to_string(sessionId));

	return sessionId;
}

namespace Modules {
    IPInspectionHook::IPInspectionHook() {
        this->patch = {
			// SetAddress
            {0x02b62d1c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_SetAddress, 0x02b62d1c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::nex::InetAddress::SetAddress, 0x02b62d1c))},
            {0x02b62e80, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_SetAddress, 0x02b62e80), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::nex::InetAddress::SetAddress, 0x02b62e80))},
            {0x02b76cf8, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_SetAddress, 0x02b76cf8), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::nex::InetAddress::SetAddress, 0x02b76cf8))},
            {0x02b82210, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_SetAddress, 0x02b82210), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::nex::InetAddress::SetAddress, 0x02b82210))},

			// GetAddress
            {0x02b61d94, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_GetAddress, 0x02b61d94), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::nex::InetAddress::GetAddress, 0x02b61d94))},
            {0x02b62e30, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_GetAddress, 0x02b62e30), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::nex::InetAddress::GetAddress, 0x02b62e30))},
            {0x02b62e30, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_GetAddress, 0x02b62e30), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::nex::InetAddress::GetAddress, 0x02b62e30))},
            {0x02b76d60, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_GetAddress, 0x02b76d60), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::nex::InetAddress::GetAddress, 0x02b76d60))},
            {0x02b7b894, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_GetAddress, 0x02b7b894), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::nex::InetAddress::GetAddress, 0x02b7b894))},

			// SendTo
            {0x02c4a038, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_SendTo, 0x02c4a038), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::common::Socket::SendTo, 0x02c4a038))},
            {0x02c4be14, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_SendTo, 0x02c4be14), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::common::Socket::SendTo, 0x02c4be14))},

			// RecvFrom
            {0x02c499f0, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_RecvFrom, 0x02c499f0), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::common::Socket::RecvFrom, 0x02c499f0))},

			// GetSessionId
            {0x027a8a7c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_GetSessionId, 0x027a8a7c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::session::Session::GetSessionId, 0x027a8a7c))},
            {0x02b34808, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) repl_GetSessionId, 0x02b34808), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::session::Session::GetSessionId, 0x02b34808))},
        };
    }

    bool IPInspectionHook::isCheatModule() {
        return false;
    }

	void IPInspectionHook::onEnable() {
		/*
		FSCmdBlock cmdBlock;

        FSFileHandle fileHandle;

		const auto now = std::chrono::system_clock::now();

		//std::string filePath = "packet_" + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
		std::string filePath = "/vol/save/80000011/packettest.txt";

        FSInitCmdBlock(&cmdBlock);
        FSERRORCHECK("Unable to open packet log file.", FSOpenFile(&Filesystem::g_fsClient, &cmdBlock, filePath.c_str(), "wr", &fileHandle, FS_ERROR_FLAG_ALL));

		logFileHandle = fileHandle;

		std::string logEntry = "test";

		std::vector<uint8_t> logBytes(logEntry.begin(), logEntry.end());
		uint8_t *logBytesData = logBytes.data();

		FSInitCmdBlock(&cmdBlock);
		FSWriteFile(&Filesystem::g_fsClient, &cmdBlock, logBytesData, logBytes.size(), 1, fileHandle, 0x0, FS_ERROR_FLAG_ALL);

		FSInitCmdBlock(&cmdBlock);
		FSFlushFile(&Filesystem::g_fsClient, &cmdBlock, fileHandle, FS_ERROR_FLAG_ALL);

		FSInitCmdBlock(&cmdBlock);
		FSCloseFile(&Filesystem::g_fsClient, &cmdBlock, fileHandle, FS_ERROR_FLAG_ALL);
		*/
	}

	void IPInspectionHook::onDisable() {
	}

    REGISTERVCLASS(IPInspectionHook)
}
