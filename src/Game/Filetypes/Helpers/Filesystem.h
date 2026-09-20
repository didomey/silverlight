#pragma once

#include<vector>
#include<string>
#include<cstdint>
#include<whb/file.h>
#include <coreinit/filesystem.h>
#include "Shared/Core/Logging.h"

#define FSERRORCHECK(ERRORTEXT, ...) \
{                                   \
    FSStatus error = __VA_ARGS__;                            \
    if(error < 0){ \
        CAFEERROR(std::to_string(error).c_str())                                \
        CAFECRASH(ERRORTEXT)\
    }                                   \
}

namespace Filesystem {
    inline FSClient g_fsClient = []() {
        FSClient client;
        //FSInit();

        CAFEINFO("Initializig Filesystem client")
        FSERRORCHECK("An error occurred during creation of filesystem client", FSAddClient(&client, FS_ERROR_FLAG_ALL));

        return client;
    }();

    std::vector<uint8_t> readFile(std::string fileName);

    void writeFile(const std::string &filePath, std::span<uint8_t> data);
    std::vector<std::string> listFileDir(std::string filePath);
}

