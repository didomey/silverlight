#include"Filesystem.h"
#include<coreinit/filesystem.h>
#include<Shared/Core/Logging.h>
#include "Internal/Logic/save.h"

#define FSERRORCHECK(ERRORTEXT, ...) \
{                                   \
    FSStatus error = __VA_ARGS__;                            \
    if(error < 0){ \
        CAFEERROR(std::to_string(error).c_str())                                \
        CAFECRASH(ERRORTEXT)\
    }                                   \
}


namespace Filesystem {
    std::vector<std::string> listFileDir(std::string filePath) {

        FSCmdBlock cmdBlock;

        FSDirectoryHandle dirHandle;

        FSInitCmdBlock(&cmdBlock);


        FSERRORCHECK("Unable to open directory!",FSOpenDir(&g_fsClient, &cmdBlock, filePath.c_str(),&dirHandle, FS_ERROR_FLAG_ALL));

        std::vector<std::string> out;

        FSDirectoryEntry dirEntry;
        while(FSReadDir(&g_fsClient, &cmdBlock, dirHandle, &dirEntry, FS_ERROR_FLAG_ALL) != FS_STATUS_END){
            out.emplace_back(dirEntry.name);
        }

        return out;
    }

    std::vector<uint8_t> readFile(std::string filePath) {

        FSCmdBlock cmdBlock;

        FSFileHandle fileHandle;
        FSStat fileStat;

        FSInitCmdBlock(&cmdBlock);
        FSStatus error = FSOpenFile(&g_fsClient, &cmdBlock, filePath.c_str(), "r", &fileHandle, FS_ERROR_FLAG_ALL);

		if (error < 0) {
			saveModules();
			return readFile(filePath);
		}

        FSInitCmdBlock(&cmdBlock);
        FSERRORCHECK("Unable to get file info!",
                     FSGetStatFile(&g_fsClient, &cmdBlock, fileHandle, &fileStat, FS_ERROR_FLAG_ALL));

        std::vector<uint8_t> fileData(fileStat.size);

        FSInitCmdBlock(&cmdBlock);
        FSERRORCHECK("Unable to read file!",
                     FSReadFile(&g_fsClient, &cmdBlock, fileData.data(), fileStat.size, 1, fileHandle, 0x0,
                                FS_ERROR_FLAG_ALL));

        FSInitCmdBlock(&cmdBlock);
        FSERRORCHECK("Unable to close file!", FSCloseFile(&g_fsClient, &cmdBlock, fileHandle, FS_ERROR_FLAG_ALL))

        return fileData;
    }

    void writeFile(const std::string &filePath, std::span<uint8_t> fData) {

        FSCmdBlock cmdBlock;

        FSFileHandle fileHandle;
        FSStat fileStat;

        FSInitCmdBlock(&cmdBlock);
        FSERRORCHECK("Unable to open file!",
                     FSOpenFile(&g_fsClient, &cmdBlock, filePath.c_str(), "w", &fileHandle,
                                FS_ERROR_FLAG_ALL));

        FSERRORCHECK("Unable to write file!",
                     FSWriteFile(&g_fsClient, &cmdBlock, (uint8_t*)fData.data(), fData.size(), 1, fileHandle, 0x0,
                                FS_ERROR_FLAG_ALL));

        FSInitCmdBlock(&cmdBlock);
        FSERRORCHECK("Unable to close file!", FSCloseFile(&g_fsClient, &cmdBlock, fileHandle, FS_ERROR_FLAG_ALL))
    }
}

