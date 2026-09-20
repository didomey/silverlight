#include"showfps.h"
#include <chrono>
#include <ctime>
#include "Internal/silverlight.h"
#include "Shared/colorconvert.h"

namespace Modules {
	ShowFPS::ShowFPS() {
		this->m_enabled = true;
	}

    void ShowFPS::start() {
    }

    void ShowFPS::stop() {
    }

    void ShowFPS::update(float deltaTime) {
    }

    void ShowFPS::render(float deltaTime) {
        float fps = (1 / deltaTime);

        const float smoothing = 0.9;
        silverlightInstance->m_averageFps =
                (silverlightInstance->m_averageFps * smoothing) + (fps * (1.0f - smoothing));

        auto uintFps = (unsigned int) silverlightInstance->m_averageFps;

		silverlightInstance->m_renderer.setTextCursor({550, 350});
		silverlightInstance->m_renderer.drawText("FPS: %2d",
            hsva2rgba({0.33 * silverlightInstance->m_averageFps / 60.0f, 1, 1, 1}),
            uintFps);
    }

    bool ShowFPS::isCheatModule() {
		return false;
    }

    REGISTERVCLASS(ShowFPS)
}
