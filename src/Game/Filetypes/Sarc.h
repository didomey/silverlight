//
// Created by tv on 07.11.23.
//

#pragma once

#include<string>
#include<vector>
#include<cstdint>

namespace SarcHeaders {
    struct SARCHeader {
        SARCHeader() {
            m_magic = *(uint32_t *) "SARC";
        }

        uint32_t m_magic; //40x53415243 == "SARC"
        uint16_t m_length = 0x14;
        uint16_t m_byteOrderMark = 0xFEFF;
        uint32_t m_fileSize = 0;
        uint32_t m_dataBeginOffset = 0;
        uint8_t m_versionMajor = 0x01;
        uint8_t m_versionMinor = 0x00;
        uint16_t m_blank = 0;
    };

    struct SFATHeader {
        SFATHeader() {
            m_magic = *(uint32_t *) "SFAT";
        }

        uint32_t m_magic; // 0x53464154 = "SFAT"
        uint16_t m_length = 0x000C;
        uint16_t m_nodeCount = 0x0000;
        uint32_t m_hashKey = 0x00000065;
    };

    struct SFATNode {
        uint32_t m_fileNameHash;
        uint32_t m_fileAttr;
        uint32_t m_beginData;
        uint32_t m_endData;
    };

    struct SFNTHeader {
        SFNTHeader() {
            m_magic = *(uint32_t *) "SFNT";
        }

        uint32_t m_magic;
        uint16_t m_length = 0x0008;
        uint16_t m_blank = 0x0000;
    };
};

class Sarc {
public:
    Sarc(const std::string &filePath);

    Sarc(const std::vector<uint8_t> &data);

    Sarc(const uint8_t *data);

    Sarc(const Sarc &) = delete;

    std::vector<uint8_t> getFile(std::string filePath);


private:
    std::vector<uint8_t> readFileNodeData(const SarcHeaders::SFATNode *node);


    const SarcHeaders::SARCHeader *m_header;
    const SarcHeaders::SFATHeader *m_sfatHeader;
    const SarcHeaders::SFATNode *m_sfatNodeArray;
    const SarcHeaders::SFNTHeader *m_sfntHeader;

    const uint8_t *m_dataSectionBegin;

    //Inner copy of the sarc files data for memory safety;
    std::vector<uint8_t> m_datastore;
};
