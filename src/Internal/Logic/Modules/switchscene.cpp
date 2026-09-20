#include "switchscene.h"
#include<Internal/Logic/modules.h>
#include<Game/Macros.h>
#include "Internal/silverlight.h"
#include<Game/Scene.h>
#include "setscenehook.h"
#include<Shared/strop.h>

FUNCBIND(_switchScene, 028c6434, uint32_t(*)(uint32_t sceneId))

void switchScene(uint32_t sceneId) {
    strcpy(g_staticMem->m_mapName, g_nextMap.data());
    _switchScene(sceneId);
}

namespace Modules {
    void SceneNameInput::receivedEntry(const std::u16string &input) {
        std::string str = u16string_to_string(input);

        Scene &scene = findClosestMatch<Scene>(str, g_scenes, [](const Scene &elem) -> std::string {
            return elem.name;
        });

        g_nextSceneId = scene.id;
    }

    REGISTERVCLASS(SceneNameInput)

    INMODULE(MapNameInput) {
        std::string str = u16string_to_string(input);

        Map &scene = findClosestMatch<Map>(str, g_maps, [](const Map &elem) -> std::string {
            return elem.dispName;
        });

        g_nextMap = scene.internalName;
    }
}
