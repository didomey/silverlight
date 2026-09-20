#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/MainMgrBase.h>
#include<Game/Assembler/ppcAssembler.h>
#include "antivision.h"
#include "Game/agl/pfx/ColorCorrection.h"

GVARBIND(mainmgrsInst, 101E2814, uint32_t)

namespace Modules {

    void AntiVision::start() {
    }

    void AntiVision::stop() {
    }

    void AntiVision::update(float deltaTime) {
		if (mainmgrsInst) {
        	uint32_t val1 = *(uint32_t *) (mainmgrsInst + 0x25c);
			if (val1) {
                uint32_t val2 = *(uint32_t *) (val1 + 8);

                if (val2) {
					agl::pfx::ColorCorrection::ColorCorrection* colorCorrection = (agl::pfx::ColorCorrection::ColorCorrection *) (val2 + 0x2900);
					colorCorrection->setHue(50.0);
                }
            }
        }
    }

    bool AntiVision::isCheatModule() {
        return true;
    }

    REGISTERVCLASS(AntiVision)
}
