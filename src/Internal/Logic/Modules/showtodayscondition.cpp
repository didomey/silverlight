#include"showclock.h"
#include <chrono>
#include <ctime>
#include "Internal/silverlight.h"

namespace Modules {

    void ShowTodaysCondition::start() {
    }

    void ShowTodaysCondition::stop() {
    }

    void ShowTodaysCondition::update(float deltaTime) {
    }

    void ShowTodaysCondition::render(float deltaTime) {
		auto start = std::chrono::system_clock::now();
		auto end = std::chrono::system_clock::now();
	 
		std::chrono::duration<double> elapsed_seconds = end-start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		std::string time(std::ctime(&end_time));

		std::string text = "Time: " + time;

		silverlightInstance->m_renderer.setTextCursor({400, 325});
        silverlightInstance->m_renderer.drawText(time);
    }

    bool ShowTodaysCondition::isCheatModule() {
		return false;
    }

    REGISTERVCLASS(ShowTodaysCondition)
}
