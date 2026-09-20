//
// Created by tv on 05.09.23.
//

#pragma once

#include<list>
#include<iostream>
#include<string>
#include<chrono>
#include"Enum.h"
#include<coreinit/debug.h>
#include<filesystem>
#include<sstream>
#include<nn/erreula.h>
#include <coreinit/memdefaultheap.h>
#include <sys/unistd.h>

#define SRCLOC \
    (std::string(__FILE__) + ":" + std::to_string(__LINE__)).c_str()

#define CAFELOGINFOSHOW(severity, ...) \
    ::Log::LogInfo{std::chrono::high_resolution_clock::now(), __FILE__, __LINE__, severity, __VA_ARGS__, true, u ## __VA_ARGS__}

#define CAFELOGINFO(severity, ...) \
    ::Log::LogInfo{std::chrono::high_resolution_clock::now(), __FILE__, __LINE__, severity, __VA_ARGS__, false, u""}

#define CAFELOGSHOW(severity, ...) \
    ::Log::Log(CAFELOGINFOSHOW(severity,__VA_ARGS__));

#define CAFELOG(severity, ...) \
    ::Log::Log(CAFELOGINFO(severity,__VA_ARGS__));

//Logs message as crash
#define CAFECRASH(...) \
    CAFELOG(::Log::LogSeverity::Crash,__VA_ARGS__)

#define CAFECRASHSHOW(...) \
    CAFELOGSHOW(::Log::LogSeverity::Crash,__VA_ARGS__)

//Logs message as error
#define CAFEERROR(...) \
    CAFELOG(::Log::LogSeverity::Error,__VA_ARGS__)

#define CAFEERRORSHOW(...) \
    CAFELOGSHOW(::Log::LogSeverity::Error,__VA_ARGS__)

//Logs message as warning
#define CAFEWARNING(...) \
    CAFELOG(::Log::LogSeverity::Warning,__VA_ARGS__)

#define CAFEWARNINGSHOW(...) \
    CAFELOGSHOW(::Log::LogSeverity::Warning,__VA_ARGS__)

//Logs message as info
#define CAFEINFO(...) \
    CAFELOG(::Log::LogSeverity::Info,__VA_ARGS__)

#define CAFEINFOSHOW(...) \
    CAFELOGSHOW(::Log::LogSeverity::Info,__VA_ARGS__)

#define CAFEVERBOSESHOW(...) \
    CAFELOGSHOW(::Log::LogSeverity::Verbose,__VA_ARGS__)

namespace Log {
    inline bool g_enableVerboseLogOut = false;

    CAFEENUM(LogSeverity,
             Crash,
             Error,
             Warning,
             Info,
             Verbose)

    struct LogInfo {
        std::chrono::high_resolution_clock::time_point m_logTime;
        const char *m_sourceFile;
        unsigned m_lineNum;
        LogSeverity m_severity;
        std::string m_message;
        bool m_show;
        const char16_t *m_u16message;
    };


    void Log(LogInfo logMsg);

    inline void Init() {
        static FSClient fsClient = {};
        FSAddClient(&fsClient, FS_ERROR_FLAG_NONE);

        // Create erreula
        nn::erreula::CreateArg createArg;
        createArg.region = nn::erreula::RegionType::Europe;
        createArg.language = nn::erreula::LangType::English;
        createArg.workMemory = MEMAllocFromDefaultHeap(nn::erreula::GetWorkMemorySize());
        createArg.fsClient = &fsClient;

        if (!nn::erreula::Create(createArg)) {
            CAFECRASH("Unable to create erreula instance")
        }
    }
}
