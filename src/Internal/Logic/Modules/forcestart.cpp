//
// Created by tv on 04.11.23.
//
#include "forcestart.h"
#include <Game/Unk.h>

namespace Modules {
    void forceStart() {
        UnkUnk *unk = getUnk();
        if (unk == nullptr) {
            return;
        }
        unk->m_unk1->m_unk1->m_shouldStartMatch = true;
    }
}
