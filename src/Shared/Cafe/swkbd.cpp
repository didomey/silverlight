//
// Created by tv on 03.12.23.
//
#include <nn/swkbd.h>
#include"swkbd.h"

bool Cafe::Swkbd::update() {
    static bool firstUpdate = true;

    if (!firstUpdate) {
        VPADStatus vpadStatus;
        VPADRead(VPAD_CHAN_0, &vpadStatus, 1, nullptr);

        nn::swkbd::ControllerInfo controllerInfo;
        controllerInfo.vpad = &vpadStatus;
        controllerInfo.kpad[0] = nullptr;
        controllerInfo.kpad[1] = nullptr;
        controllerInfo.kpad[2] = nullptr;
        controllerInfo.kpad[3] = nullptr;
        nn::swkbd::Calc(controllerInfo);

        if (nn::swkbd::IsNeedCalcSubThreadFont()) {
            nn::swkbd::CalcSubThreadFont();
        }

        if (nn::swkbd::IsNeedCalcSubThreadPredict()) {
            nn::swkbd::CalcSubThreadPredict();
        }

        nn::swkbd::DrawTV();
        nn::swkbd::DrawDRC();
        return true;
    }

    firstUpdate = false;

    return false;
}
