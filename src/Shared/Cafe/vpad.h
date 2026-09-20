#pragma once

struct Inputs {
    bool unused: 0x1;
    bool StickLEmulationLeft: 0x1;
    bool StickLEmulationRight: 0x1;
    bool StickLEmulationUp: 0x1;
    bool StickLEmulationDown: 0x1;
    bool StickREmulationLeft: 0x1;
    bool StickREmulationRight: 0x1;
    bool StickREmulationUp: 0x1;
    bool StickREmulationDown: 0x1;
    bool unused2: 0x4;
    bool StickLButton: 0x1;
    bool StickRButton: 0x1;
    bool ButtonTV: 0x1;
    bool ButtonA: 0x1;
    bool ButtonB: 0x1;
    bool ButtonX: 0x1;
    bool ButtonY: 0x1;
    bool ButtonLeft: 0x1;
    bool ButtonRight: 0x1;
    bool ButtonUp: 0x1;
    bool ButtonDown: 0x1;
    bool ButtonZL: 0x1;
    bool ButtonZR: 0x1;
    bool ButtonL: 0x1;
    bool ButtonR: 0x1;
    bool ButtonPlus: 0x1;
    bool ButtonMinus: 0x1;
    bool ButtonHome: 0x1;
    bool ButtonSync: 0x1;
};

static_assert(sizeof(Inputs) == sizeof(uint32_t));