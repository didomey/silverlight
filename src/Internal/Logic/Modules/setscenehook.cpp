//
// Created by tv on 16.12.23.
//
#include<Internal/Logic/modules.h>
#include<Game/Macros.h>
#include "Internal/silverlight.h"
#include<Game/Scene.h>
#include "setscenehook.h"

int currSceneId = 0;

GVARBIND(g_setSceneFunc, 101e6a94, ESC(uint32_t(*)(uint32_t param_1, int * param_2)))
FUNCBIND(setScene, 028a0418, uint32_t(*)(uint32_t param_1, int * param_2))

uint32_t replSetScene(uint32_t sceneId, int *unk) {
    static uint32_t lastSceneId = 0;

	currSceneId = sceneId;

    if (sceneId == 7) {
        if (Game::Scene::isPublicMatchingScene(lastSceneId)) {
            silverlightInstance->m_currentlyInPublicMatch = true;
        }
    } else
        silverlightInstance->m_currentlyInPublicMatch = false;

    lastSceneId = sceneId;
    return setScene(sceneId, unk);
}


namespace Modules {
    class SetSceneHook : public UpdateModule {
    VCLASS (SetSceneHook, ESC({&UpdateModule::classInfo, nullptr}))
    public:
        SetSceneHook() {
			this->m_enabled = true;
            g_setSceneFunc = replSetScene;
        };


        void update(float) override {
            g_setSceneFunc = replSetScene;
        }

        bool isCheatModule() override { return false; };
    };

    REGISTERVCLASS(SetSceneHook)

    class SetSceneHookPatch : public PatchModule {
    VCLASS (SetSceneHookPatch, ESC({&PatchModule::classInfo, nullptr}))
    public:
        SetSceneHookPatch() {
            this->patch = {
                    {0x028a07c8, {"nop", "stw r0,0x6a94(r10)"}}
            };
            this->enablePatch();
        };

        bool isCheatModule() override { return false; };
    };

    REGISTERVCLASS(SetSceneHookPatch)
}
