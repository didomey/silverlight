//
// Created by tv on 18.11.23.
//

#pragma once

#include"Macros.h"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

typedef unsigned char undefined;

typedef unsigned char byte;
typedef unsigned int dword;
typedef long long longlong;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long undefined6;
typedef unsigned long long undefined8;
typedef unsigned short ushort;
typedef unsigned short word;
typedef struct DebugTextRenderer DebugTextRenderer, *PDebugTextRenderer;

#pragma pack(push, 1)

struct DebugTextRenderer {
    undefined4 field0_0x0;
    undefined4 field1_0x4;
    undefined4 field2_0x8;
    int field3_0xc;
    //float field4_0x10;
    //float field5_0x14;
    glm::vec2 m_textCursor;
    glm::vec2 m_textSize;
    //float field8_0x20;
    //float field9_0x24;
    //float field10_0x28;
    //float field11_0x2c;
    glm::vec4 m_color; // ?
    glm::vec2 m_kerneling;
    undefined4 field14_0x38;
    float field15_0x3c;
    undefined4 field16_0x40;
    undefined4 field17_0x44;
    undefined4 field18_0x48;
    undefined *field19_0x4c;
};

#pragma pack(pop)

ENSURE_OFFSET(DebugTextRenderer, field0_0x0, 0x0);
ENSURE_OFFSET(DebugTextRenderer, field1_0x4, 0x4);
ENSURE_OFFSET(DebugTextRenderer, field2_0x8, 0x8);
ENSURE_OFFSET(DebugTextRenderer, field3_0xc, 0xc);
//ENSURE_OFFSET(DebugTextRenderer, field4_0x10, 0x10);
//ENSURE_OFFSET(DebugTextRenderer, field5_0x14, 0x14);
//ENSURE_OFFSET(DebugTextRenderer, field6_0x18, 0x18);
//ENSURE_OFFSET(DebugTextRenderer, field7_0x1c, 0x1c);
//ENSURE_OFFSET(DebugTextRenderer, field8_0x20, 0x20);
//ENSURE_OFFSET(DebugTextRenderer, field9_0x24, 0x24);
//ENSURE_OFFSET(DebugTextRenderer, field10_0x28, 0x28);
//ENSURE_OFFSET(DebugTextRenderer, field11_0x2c, 0x2c);
//ENSURE_OFFSET(DebugTextRenderer, field12_0x30, 0x30);
//ENSURE_OFFSET(DebugTextRenderer, field13_0x34, 0x34);
ENSURE_OFFSET(DebugTextRenderer, field14_0x38, 0x38);
ENSURE_OFFSET(DebugTextRenderer, field15_0x3c, 0x3c);
ENSURE_OFFSET(DebugTextRenderer, field16_0x40, 0x40);
ENSURE_OFFSET(DebugTextRenderer, field17_0x44, 0x44);
ENSURE_OFFSET(DebugTextRenderer, field18_0x48, 0x48);
ENSURE_OFFSET(DebugTextRenderer, field19_0x4c, 0x4c);

