//
// Created by tv on 03.11.23.
//
#include "StaticMem.h"

Cmn::StaticMem::StaticMem *getStaticMem() {
    return *(Cmn::StaticMem::StaticMem **) STATIC_MEM_PTR;
}
