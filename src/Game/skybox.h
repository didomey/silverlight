struct SkyboxInfo {
	std::string name;
	std::string internalName;
};

inline std::array<SkyboxInfo, 5> skyboxes = {
	{
        {"VR_SkyDaytime00", "VR_SkyDaytime00"},
        {"VR_SkyNight00", "VR_SkyNight00"},
        {"VR_SkyTwilight00", "VR_SkyTwilight00"},
        {"VR_SkyDayTudura", "VR_SkyDayTudura"},
        {"VR_DomeMonitorSkyWorld", "VR_DomeMonitorSkyWorld"},
	}
};
