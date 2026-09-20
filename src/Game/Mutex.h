//
// Created by tv on 28.11.23.
//

#pragma once

#include"Macros.h"

namespace Game::Mutex {
    struct Mutex;

    FUNCBIND(tryLock, 02902fa4, bool(*)(Mutex * lock))
    FUNCBIND(unlock, 02902fd0, void(*)(Mutex * lock))
}