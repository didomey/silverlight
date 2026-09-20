//
// Created by tv on 15.11.23.
//

#include "blastershooterrapidfire.h"
#include<Shared/Core/Assert.h>
#include<cstdint>

void BlasterShooterRapidfire::start() {

}

void BlasterShooterRapidfire::stop() {

}

void BlasterShooterRapidfire::update(float deltaTime) {
    /*
    uint32_t ptr1 = *(uint32_t *) 0x106E417C;
    CAFEASSERT(0x10000000 <= ptr1 && ptr1 <= 0x50000000);
    uint32_t ptr2 = *(uint32_t *) ptr1 + 0x578;
    CAFEASSERT(0x10000000 <= ptr2 && ptr2 <= 0x50000000);
    uint32_t ptr3 = *(uint32_t *) ptr2 + 0x30;
    CAFEASSERT(0x10000000 <= ptr3 && ptr3 <= 0x50000000);
    uint32_t ptr4 = *(uint32_t *) ptr2 - 0x344;
    CAFEASSERT(0x10000000 <= ptr4 && ptr4 <= 0x50000000);

    *(float *) (ptr4 + 0x48) = 1.0f;
    *(uint32_t *) (ptr4 + 0x48) = 0x0;
    */

}

bool BlasterShooterRapidfire::isCheatModule() {
    return true;
}

REGISTERVCLASS(BlasterShooterRapidfire)
