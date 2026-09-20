//
// Created by tv on 07.11.23.
//

#include "Sarc.h"
#include"Helpers/Filesystem.h"
#include "Shared/Core/Logging.h"

using namespace SarcHeaders;

static uint32_t getHash(std::string fileName, uint32_t key = 0x00000065) {
    uint32_t result = 0;

    for (const char &c: fileName) {
        result = c + result * key;
    }

    return result;
}

Sarc::Sarc(const std::string &filePath) : Sarc(Filesystem::readFile(filePath)) {}

Sarc::Sarc(const std::vector<uint8_t> &data) : Sarc(data.data()) {}


Sarc::Sarc(const uint8_t *data) {
    SARCHeader *header = (SARCHeader *) data;


    //Ensure that the file we are reading is actually a sarc file
    if (header->m_magic != *(uint32_t *) "SARC")
        CAFEERROR("Attempted to read non-sarc file as sarc file!");


    //Copy data to internal data.
    m_datastore = std::vector<uint8_t>(header->m_fileSize);
    memcpy(m_datastore.data(), data, header->m_fileSize);
    m_header = (SARCHeader *) m_datastore.data();

    const uint8_t *dataPtr = m_datastore.data();
    //skip
    dataPtr += m_header->m_length;

    m_sfatHeader = (SFATHeader *) dataPtr;
    //Ensure that we are still reading in the correct place
    if (m_sfatHeader->m_magic != *(uint32_t *) "SFAT")
        CAFEERROR("Unable to find sfat header");

    dataPtr += m_sfatHeader->m_length;

    m_sfatNodeArray = (SFATNode *) dataPtr;

    dataPtr += sizeof(SFATNode) * m_sfatHeader->m_nodeCount;

    m_sfntHeader = (SFNTHeader *) dataPtr;

    if (m_sfntHeader->m_magic != *(uint32_t *) "SFNT")
        CAFEERROR("Unable to find sfat header");

    m_dataSectionBegin = m_datastore.data() + header->m_dataBeginOffset;
}

std::vector<uint8_t> Sarc::getFile(std::string filePath) {
    //Do binary search on the sfat header array for file name hash.

    uint32_t fileHash = getHash(filePath, m_sfatHeader->m_hashKey);

    uint16_t split = m_sfatHeader->m_nodeCount / 2;
    const SFATNode *node = m_sfatNodeArray + split;

    while (node->m_fileNameHash != fileHash) {
        if (split == 1) {
            CAFEERROR(("Unable to read file from sarc: " + filePath).c_str())
            return {};
        }
        split /= 2;
        if (node->m_fileNameHash < fileHash)
            node += split;
        else
            node -= split;
    }

    return readFileNodeData(node);
}

std::vector<uint8_t> Sarc::readFileNodeData(const SFATNode *node) {
    return {
            m_dataSectionBegin + node->m_beginData, //Beginning of the data to copy
            m_dataSectionBegin + node->m_endData    //End of the data to copy
    };
}
