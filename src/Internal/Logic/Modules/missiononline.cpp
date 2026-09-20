//
// Created by tv on 04.11.23.
//
#include"noautocameramovement.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgr.h>
#include<Game/Assembler/ppcAssembler.h>

void crash_025F8B38() {

}






void crash_0229BA14() {
}





void crash_0229BADC() {
}





void crash_025F9704() {
}





void crash_0229D3D8() {
}





void crash_023E47E8() {
}






void crash_025F8BEC() {
}






void crash_022C5A88() {
}







void crash_023EDBEC() {
}





void crash_02372A34() {
}





void crash_02379440() {
}





void crash_025FCEE4() {
}





void crash_02600280() {
}






void crash_023EDD88() {
}





void crash_025FD9B8() {
}




void crash_023EDCE8() {
}





void crash_025FD500() {
}




void crash_025FCEC4() {
}





void crash_026357BC() {
}




void crash_023D4670() {
}




void crash_023A77E0() {
}





void crash_025FCF98() {
}







void crash_02378CEC() {
}






void crash_02375234() {
}






void crash_02373958() {
}





void crash_02659B78() {
}






void crash_0252044C() {
}







void crash_025202A0() {
}






namespace Modules {
    MissionOnlineCrashFixes::MissionOnlineCrashFixes() {
        this->patch = {
                {0x02664f20, PatchElement("nop", DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x02057c74, 0x02664f20))},
                {0x0269D170, PatchElement("li r12, 1", "li r12, 0xec(r12)")},
        };
		this->disablePatch();
    }

    bool MissionOnlineCrashFixes::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(MissionOnlineCrashFixes)
}
