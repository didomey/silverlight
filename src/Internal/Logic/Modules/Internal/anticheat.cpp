#include <unordered_map>
#include <vector>
#include <set>
#include <unordered_set>

#include "anticheat.h"
#include "Shared/Core/Logging.h"
#include "Shared/Core/Assert.h"
#include "Shared/CemuBind.h"
#include<Game/Assembler/ppcAssembler.h>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/mat3x3.hpp>
#include<Shared/Cafe/vpad.h>
#include "Shared/strop.h"
#include "Game/PlayerTroubleUnk.h"
#include "Game/PlayerClone.h"
#include "Internal/Logic/Modules/playereventhook.h"
#include "glm/gtx/string_cast.hpp"
#include "Game/BulletCloneHandle.h"
#include "Game/Macros.h"
#include "Game/PacketBulletCloneEvent.h"
#include "Game/PacketPaintCloneEvent.h"
#include "Game/PaintCloneEvent.h"
#include "Game/PaintCloneHandle.h"
#include "Game/PlayerNetState.h"
#include "Game/BossUploadDataMaker.h"
#include "Game/Filetypes/Helpers/Filesystem.h"
#include "Game/nn/pia/transport/Station.h"
#include "Game/nn/pia/transport/StationConnectionInfoTable.h"
#include "Game/nn/pia/transport/StationConnectionInfo.h"
#include "Game/nn/pia/transport/StationManager.h"
#include "Internal/silverlight.h"
#include "Internal/Logic/Modules/switchscene.h"
#include "Game/Lp/Utl/Matching.h"
#include "Game/UniqueID.h"
#include "Game/enl/PiaUtil.h"
#include "Game/enl/IDManager.h"
#include "Shared/netop.h"
#include "Game/nn/pia/common/Socket.h"
#include "Game/nn/pia/session/Session.h"
#include "Game/nn/nex/InetAddress.h"
#include "Game/nn/pia/session/Mesh.h"
#include "Game/Cmn/Def/Ability.h"
#include "Game/RequestPaintArg.h"
#include "Game/StaticMem.h"
#include "Game/Lp/Net.h"

#include "Shared/CemuBind.h"

#define NOKRNL_DBG 1

#define SMOOTHING 0.4
#define MIN_PING_COUNT 200
#define MAX_FLAG_COUNT 10

namespace NoKrnl {
	#define COMMON_EVENT_BUF_SIZE 512

	enum class nokrnl_MainWeapon {
		SplooshOMatic=0x00,
		NeoSplooshOMatic=0x01,
		SplooshOMatic7=0x02,
		SplattershotJr=0x03,
		CustomSplattershotJr=0x04,
		SplashOMatic=0x05,
		NeoSplashOMatic=0x06,
		AerosprayMG=0x07,
		AerosprayRG=0x08,
		AerosprayPG=0x09,
		Splattershot=0x0A,
		TentatekSplattershot=0x0B,
		WasabiSplattershot=0x0C,
		HeroShotReplica=0x0D,
		OctoshotReplica=0x0E,
		_52Gal=0x0F,
		_52GalDeco=0x10,
		NZap85=0x11,
		NZap89=0x12,
		NZap83=0x13,
		SplattershotPro=0x14,
		ForgeSplattershotPro=0x15,
		BerrySplattershotPro=0x16,
		_96Gal=0x17,
		_96GalDeco=0x18,
		DualSquelcher=0x19,
		CustomDualSquelcher=0x1A,
		JetSquelcher=0x1B,
		CustomJetSquelcher=0x1C,
		LunaBlaster=0x1D,
		LunaBlasterNeo=0x1E,
		Blaster=0x1F,
		CustomBlaster=0x20,
		RangeBlaster=0x21,
		CustomRangeBlaster=0x22,
		GrimRangeBlaster=0x23,
		RapidBlaster=0x24,
		RapidBlasterDeco=0x25,
		RapidBlasterPro=0x26,
		RapidBlasterProDeco=0x27,
		L3Nozzlenose=0x28,
		L3NozzlenoseD=0x29,
		H3Nozzlenose=0x2A,
		H3NozzlenoseD=0x2B,
		CherryH3Nozzlenose=0x2C,
		CarbonRoller=0x2D,
		CarbonRollerDeco=0x2E,
		SplatRoller=0x2F,
		KrakOnSplatRoller=0x30,
		CoroCoroSplatRoller=0x31,
		HeroRollerReplica=0x32,
		DynamoRoller=0x33,
		GoldDynamoRoller=0x34,
		TemperedDynamoRoller=0x35,
		Inkbrush=0x36,
		InkbrushNouveau=0x37,
		PermanentInkbrush=0x38,
		Octobrush=0x39,
		OctobrushNouveau=0x3A,
		ClassicSquiffer=0x3B,
		NewSquiffer=0x3C,
		FreshSquiffer=0x3D,
		SplatCharger=0x3E,
		KelpSplatCharger=0x3F,
		BentoSplatCharger=0x40,
		HeroChargerReplica=0x41,
		Splatterscope=0x42,
		KelpSplatterscope=0x43,
		BentoSplatterscope=0x44,
		ELiter3K=0x45,
		CustomELiter3K=0x46,
		ELiter3KScope=0x47,
		CustomELiter3KScope=0x48,
		Bamboozler14MKI=0x49,
		Bamboozler14MKII=0x4A,
		Bamboozler14MKIII=0x4B,
		Slosher=0x4C,
		SlosherDeco=0x4D,
		SodaSlosher=0x4E,
		TriSlosher=0x4F,
		TriSlosherNouveau=0x50,
		SloshingMachine=0x51,
		SloshingMachineNeo=0x52,
		MiniSplatling=0x53,
		ZinkMiniSplatling=0x54,
		RefurbishedMiniSplatling=0x55,
		HeavySplatling=0x57,
		HeavySplatlingDeco=0x57,
		HeavySplatlingRemix=0x58,
		HydraSplatling=0x59,
		CustomHydraSplatling=0x5A,
		HeroShotLvl0=0x5B,
		HeroShotLvl1=0x5C,
		HeroShotLvl2=0x5D,
		HeroShotLvl3=0x5E,
		HeroRoller=0x5F,
		HeroCharger=0x60,
		BigBallA=0x61,
		BigBallB=0x62,
		OctoshotLvl0=0x63,
		OctoshotLvl1=0x64,
		OctoshotLvl2=0x65,
		OctoshotLvl3=0x66,
		RollerKingsquid=0x67
	};

	enum class nokrnl_SubWeapon {
		SplatBomb=0x00,
		SuctionBomb=0x01,
		BurstBomb=0x02,
		Seeker=0x03,
		PointSensor= 0x04,
		InkMine=0x05,
		Sprinkler=0x06,
		SquidBeakon=0x07,
		SplashWall=0x08,
		Disruptor=0x09,
	};

	enum class nokrnl_SpecialWeapon {
		Inkzooka=0x00,
		KillerWail=0x01,
		Inkstrike=0x02,
		Bubbler=0x03,
		BombRush=0x04,
		Kraken=0x05,
		Echolocator=0x06,
		Rainmaker=0x07,
	};

	struct nokrnl_WeaponSet {
		nokrnl_MainWeapon mainWeapon;
		nokrnl_SubWeapon subWeapon;
		nokrnl_SpecialWeapon specialWeapon;

		nokrnl_WeaponSet(nokrnl_MainWeapon _mainWeapon, nokrnl_SubWeapon _subWeapon, nokrnl_SpecialWeapon _specialWeapon) : mainWeapon(_mainWeapon), subWeapon(_subWeapon), specialWeapon(_specialWeapon) {}

		bool operator==(const nokrnl_WeaponSet& other) const {
            return this->mainWeapon == other.mainWeapon && this->subWeapon == other.subWeapon && this->specialWeapon == other.specialWeapon;
        }
	};

	struct nokrnl_WeaponSetComparator {
		bool operator()(const nokrnl_WeaponSet& ws1, const nokrnl_WeaponSet& ws2) const {
			if (ws1.mainWeapon != ws2.mainWeapon)
				return ws1.mainWeapon < ws2.mainWeapon;
			if (ws1.subWeapon != ws2.subWeapon)
				return ws1.subWeapon < ws2.subWeapon;
			return ws1.specialWeapon < ws2.specialWeapon;
		}
	};

	static std::set<nokrnl_WeaponSet, nokrnl_WeaponSetComparator> nokrnl_weaponSets = {
		{nokrnl_MainWeapon::_52Gal, nokrnl_SubWeapon::SplashWall, nokrnl_SpecialWeapon::KillerWail},
		{nokrnl_MainWeapon::_52GalDeco, nokrnl_SubWeapon::Seeker, nokrnl_SpecialWeapon::Inkstrike},
		{nokrnl_MainWeapon::_96Gal, nokrnl_SubWeapon::Sprinkler, nokrnl_SpecialWeapon::Echolocator},
		{nokrnl_MainWeapon::_96GalDeco, nokrnl_SubWeapon::SplashWall, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::AerosprayMG, nokrnl_SubWeapon::Seeker, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::AerosprayPG, nokrnl_SubWeapon::BurstBomb, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::AerosprayRG, nokrnl_SubWeapon::InkMine, nokrnl_SpecialWeapon::Inkstrike},
		{nokrnl_MainWeapon::Bamboozler14MKI, nokrnl_SubWeapon::SplashWall, nokrnl_SpecialWeapon::KillerWail},
		{nokrnl_MainWeapon::Bamboozler14MKII, nokrnl_SubWeapon::Disruptor, nokrnl_SpecialWeapon::Echolocator},
		{nokrnl_MainWeapon::Bamboozler14MKIII, nokrnl_SubWeapon::BurstBomb, nokrnl_SpecialWeapon::Inkstrike},
		{nokrnl_MainWeapon::BentoSplatCharger, nokrnl_SubWeapon::SplashWall, nokrnl_SpecialWeapon::Echolocator},
		{nokrnl_MainWeapon::BentoSplatterscope, nokrnl_SubWeapon::SplashWall, nokrnl_SpecialWeapon::Echolocator},
		{nokrnl_MainWeapon::BerrySplattershotPro, nokrnl_SubWeapon::SuctionBomb, nokrnl_SpecialWeapon::BombRush},
		{nokrnl_MainWeapon::Blaster, nokrnl_SubWeapon::Disruptor, nokrnl_SpecialWeapon::KillerWail},
		{nokrnl_MainWeapon::CarbonRoller, nokrnl_SubWeapon::BurstBomb, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::CarbonRollerDeco, nokrnl_SubWeapon::Seeker, nokrnl_SpecialWeapon::BombRush},
		{nokrnl_MainWeapon::CherryH3Nozzlenose, nokrnl_SubWeapon::SplashWall, nokrnl_SpecialWeapon::Bubbler},
		{nokrnl_MainWeapon::ClassicSquiffer, nokrnl_SubWeapon::PointSensor, nokrnl_SpecialWeapon::Bubbler},
		{nokrnl_MainWeapon::CoroCoroSplatRoller, nokrnl_SubWeapon::SplashWall, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::CustomBlaster, nokrnl_SubWeapon::PointSensor, nokrnl_SpecialWeapon::Bubbler},
		{nokrnl_MainWeapon::CustomDualSquelcher, nokrnl_SubWeapon::SquidBeakon, nokrnl_SpecialWeapon::KillerWail},
		{nokrnl_MainWeapon::CustomELiter3K, nokrnl_SubWeapon::SquidBeakon, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::CustomELiter3KScope, nokrnl_SubWeapon::SquidBeakon, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::CustomHydraSplatling, nokrnl_SubWeapon::Sprinkler, nokrnl_SpecialWeapon::Bubbler},
		{nokrnl_MainWeapon::CustomJetSquelcher, nokrnl_SubWeapon::BurstBomb, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::CustomRangeBlaster, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::CustomSplattershotJr, nokrnl_SubWeapon::Disruptor, nokrnl_SpecialWeapon::Echolocator},
		{nokrnl_MainWeapon::DualSquelcher, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::Echolocator},
		{nokrnl_MainWeapon::DynamoRoller, nokrnl_SubWeapon::Sprinkler, nokrnl_SpecialWeapon::Echolocator},
		{nokrnl_MainWeapon::ELiter3K, nokrnl_SubWeapon::BurstBomb, nokrnl_SpecialWeapon::Echolocator},
		{nokrnl_MainWeapon::ELiter3KScope, nokrnl_SubWeapon::BurstBomb, nokrnl_SpecialWeapon::Echolocator},
		{nokrnl_MainWeapon::ForgeSplattershotPro, nokrnl_SubWeapon::PointSensor, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::FreshSquiffer, nokrnl_SubWeapon::SuctionBomb, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::GoldDynamoRoller, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::Inkstrike},
		{nokrnl_MainWeapon::GrimRangeBlaster, nokrnl_SubWeapon::BurstBomb, nokrnl_SpecialWeapon::KillerWail},
		{nokrnl_MainWeapon::H3Nozzlenose, nokrnl_SubWeapon::SuctionBomb, nokrnl_SpecialWeapon::Echolocator},
		{nokrnl_MainWeapon::H3NozzlenoseD, nokrnl_SubWeapon::PointSensor, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::HeavySplatling, nokrnl_SubWeapon::SplashWall, nokrnl_SpecialWeapon::Inkstrike},
		{nokrnl_MainWeapon::HeavySplatlingDeco, nokrnl_SubWeapon::PointSensor, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::HeavySplatlingRemix, nokrnl_SubWeapon::Sprinkler, nokrnl_SpecialWeapon::KillerWail},
		{nokrnl_MainWeapon::HeroChargerReplica, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::BombRush},
		{nokrnl_MainWeapon::HeroRollerReplica, nokrnl_SubWeapon::SuctionBomb, nokrnl_SpecialWeapon::KillerWail},
		{nokrnl_MainWeapon::HeroShotReplica, nokrnl_SubWeapon::BurstBomb, nokrnl_SpecialWeapon::BombRush},
		{nokrnl_MainWeapon::HydraSplatling, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::Echolocator},
		{nokrnl_MainWeapon::Inkbrush, nokrnl_SubWeapon::Sprinkler, nokrnl_SpecialWeapon::Inkstrike},
		{nokrnl_MainWeapon::InkbrushNouveau, nokrnl_SubWeapon::InkMine, nokrnl_SpecialWeapon::Bubbler},
		{nokrnl_MainWeapon::JetSquelcher, nokrnl_SubWeapon::SplashWall, nokrnl_SpecialWeapon::Inkstrike},
		{nokrnl_MainWeapon::KelpSplatCharger, nokrnl_SubWeapon::Sprinkler, nokrnl_SpecialWeapon::KillerWail},
		{nokrnl_MainWeapon::KelpSplatterscope, nokrnl_SubWeapon::Sprinkler, nokrnl_SpecialWeapon::KillerWail},
		{nokrnl_MainWeapon::KrakOnSplatRoller, nokrnl_SubWeapon::SquidBeakon, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::L3Nozzlenose, nokrnl_SubWeapon::Disruptor, nokrnl_SpecialWeapon::KillerWail},
		{nokrnl_MainWeapon::L3NozzlenoseD, nokrnl_SubWeapon::BurstBomb, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::LunaBlaster, nokrnl_SubWeapon::InkMine, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::LunaBlasterNeo, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::BombRush},
		{nokrnl_MainWeapon::MiniSplatling, nokrnl_SubWeapon::SuctionBomb, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::NZap83, nokrnl_SubWeapon::PointSensor, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::NZap85, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::Echolocator},
		{nokrnl_MainWeapon::NZap89, nokrnl_SubWeapon::Sprinkler, nokrnl_SpecialWeapon::Inkstrike},
		{nokrnl_MainWeapon::NeoSplashOMatic, nokrnl_SubWeapon::BurstBomb, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::NeoSplooshOMatic, nokrnl_SubWeapon::PointSensor, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::NewSquiffer, nokrnl_SubWeapon::InkMine, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::Octobrush, nokrnl_SubWeapon::SquidBeakon, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::OctobrushNouveau, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::OctoshotReplica, nokrnl_SubWeapon::SuctionBomb, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::PermanentInkbrush, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::RangeBlaster, nokrnl_SubWeapon::SplashWall, nokrnl_SpecialWeapon::Inkstrike},
		{nokrnl_MainWeapon::RapidBlaster, nokrnl_SubWeapon::InkMine, nokrnl_SpecialWeapon::Bubbler},
		{nokrnl_MainWeapon::RapidBlasterDeco, nokrnl_SubWeapon::SuctionBomb, nokrnl_SpecialWeapon::BombRush},
		{nokrnl_MainWeapon::RapidBlasterPro, nokrnl_SubWeapon::Seeker, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::RapidBlasterProDeco, nokrnl_SubWeapon::Disruptor, nokrnl_SpecialWeapon::KillerWail},
		{nokrnl_MainWeapon::RefurbishedMiniSplatling, nokrnl_SubWeapon::BurstBomb, nokrnl_SpecialWeapon::BombRush},
		{nokrnl_MainWeapon::Slosher, nokrnl_SubWeapon::BurstBomb, nokrnl_SpecialWeapon::Inkstrike},
		{nokrnl_MainWeapon::SlosherDeco, nokrnl_SubWeapon::SplashWall, nokrnl_SpecialWeapon::Kraken},
		{nokrnl_MainWeapon::SloshingMachine, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::BombRush},
		{nokrnl_MainWeapon::SloshingMachineNeo, nokrnl_SubWeapon::PointSensor, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::SodaSlosher, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::SplashOMatic, nokrnl_SubWeapon::SuctionBomb, nokrnl_SpecialWeapon::BombRush},
		{nokrnl_MainWeapon::SplatCharger, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::BombRush},
		{nokrnl_MainWeapon::SplatRoller, nokrnl_SubWeapon::SuctionBomb, nokrnl_SpecialWeapon::KillerWail},
		{nokrnl_MainWeapon::Splatterscope, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::BombRush},
		{nokrnl_MainWeapon::Splattershot, nokrnl_SubWeapon::BurstBomb, nokrnl_SpecialWeapon::BombRush},
		{nokrnl_MainWeapon::SplattershotJr, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::Bubbler},
		{nokrnl_MainWeapon::SplattershotPro, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::Inkstrike},
		{nokrnl_MainWeapon::SplooshOMatic, nokrnl_SubWeapon::SquidBeakon, nokrnl_SpecialWeapon::KillerWail},
		{nokrnl_MainWeapon::SplooshOMatic7, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::TemperedDynamoRoller, nokrnl_SubWeapon::Seeker, nokrnl_SpecialWeapon::KillerWail},
		{nokrnl_MainWeapon::TentatekSplattershot, nokrnl_SubWeapon::SuctionBomb, nokrnl_SpecialWeapon::Inkzooka},
		{nokrnl_MainWeapon::TriSlosher, nokrnl_SubWeapon::Disruptor, nokrnl_SpecialWeapon::Bubbler},
		{nokrnl_MainWeapon::TriSlosherNouveau, nokrnl_SubWeapon::Seeker, nokrnl_SpecialWeapon::Echolocator},
		{nokrnl_MainWeapon::WasabiSplattershot, nokrnl_SubWeapon::SplatBomb, nokrnl_SpecialWeapon::Inkstrike},
		{nokrnl_MainWeapon::ZinkMiniSplatling, nokrnl_SubWeapon::Disruptor, nokrnl_SpecialWeapon::Bubbler}
	};

	enum nokrnl_SubWeaponID {
		SUB_SPLAT,
		SUB_SUCTION,
		SUB_BURST,
		SUB_SEEKER,
		SUB_SENSOR,
		SUB_MINE,
		SUB_SPRINKLER,
		SUB_BEAKON,
		SUB_WALL,
		SUB_DISRUPTOR,
	};

	enum class nokrnl_DetectionType {
		RapidFire,
		InvalidInkTank,
		InvalidWeaponSet,
		InvalidAbilities,
		InstaCover,
		FastRespawn,
		BadMovement,
		GodMode,
		InvalidMode,
		InvalidMap,
	};

	const std::unordered_map<nokrnl_DetectionType, std::string> nokrnl_DetectionType_strings = {
		{ nokrnl_DetectionType::RapidFire, "Rapid Fire" },
		{ nokrnl_DetectionType::InvalidInkTank, "Invalid Ink Tank" },
		{ nokrnl_DetectionType::InvalidWeaponSet, "Invalid WeaponSet" },
		{ nokrnl_DetectionType::InvalidAbilities, "Invalid Abilities" },
		{ nokrnl_DetectionType::InstaCover, "Insta Cover" },
		{ nokrnl_DetectionType::FastRespawn, "Fast Respawn" },
		{ nokrnl_DetectionType::BadMovement, "Bad Movement" },
		{ nokrnl_DetectionType::GodMode, "God Mode" },
		{ nokrnl_DetectionType::InvalidMode, "Invalid Mode" },
		{ nokrnl_DetectionType::InvalidMap, "Invalid Map" },
	};

	struct nokrnl_PlayerNetStatus {
		// enl pid
		uint32_t pid;
		nn::pia::common::InetAddress::InetAddress address;
		Cmn::PlayerInfo::PlayerInfo playerInfo;
	};

	struct nokrnl_PlayerEventStatus {
		bool alive = true;
	};

	struct nokrnl_PlayerStatus {
		float averageDeltaTime;
		int pingCount = 0;
		int consecutiveEmptyTankShots = 0;
		bool flagWarningSent = false;

		std::chrono::_V2::system_clock::time_point prevUpdateTime = {};

		std::optional<std::chrono::_V2::system_clock::time_point> deathTime = std::nullopt;

		std::vector<nokrnl_DetectionType> flags = {};

		nokrnl_PlayerEventStatus eventStatus = {};
		nokrnl_PlayerNetStatus netStatus = {};

		void addFlag(nokrnl_DetectionType flag) {
#ifdef NOKRNL_DBG
			CAFEINFO("Received flag \"" + NoKrnl::nokrnl_DetectionType_strings.at(flag) + "\" from player \"" + std::to_string(this->netStatus.pid) + "\" with IP address \"" + formatIpBytes(this->netStatus.address.address) + ":" + std::to_string(this->netStatus.address.port) + "\"");
#endif

			if (!this->flagWarningSent) {
				this->flagWarningSent = true;
			}

			this->flags.push_back(flag);
		}

		void addMaxConfidenceFlag(nokrnl_DetectionType flag) {
#ifdef NOKRNL_DBG
			CAFEINFO("Player " + std::to_string(this->netStatus.pid) + " triggered max confidence flag.");
#endif

			while (!this->isOfficiallyFlagged()) this->addFlag(flag);
		}

		bool isOfficiallyFlagged() const {
			return this->flags.size() >= MAX_FLAG_COUNT;
		}
	};

	static NoKrnl::nokrnl_PlayerStatus nokrnl_playerStatuses[8] = {};

	struct nokrnl_LogReportData {
		std::vector<nokrnl_DetectionType> flags;
		Cmn::PlayerInfo::PlayerInfo playerInfo;
		uint32_t playerIdx;
		uint32_t pid;
		uint32_t ipAddress;
		bool isHost;
	};

	void nokrnl_saveLogReports(void* state, std::vector<nokrnl_LogReportData> logReports) {
		for (const auto& logReport : logReports) {
#ifdef NOKRNL_DBG
			CAFEINFO("Sending log for player #" + std::to_string(logReport.playerIdx));
#endif

			std::vector<uint32_t> intFlags = {};
			for (const auto& flag : logReport.flags) {
				intFlags.push_back(static_cast<uint32_t>(flag));
			}

			SLInternalNetLogMatch(&state, Lp::Sys::BossUploadDataMaker::getSessionID(), logReport.playerIdx, logReport.playerInfo, intFlags.data(), intFlags.size());
		}

		/*
		std::string log = {};
		std::string fileName = "log_" + std::to_string(Lp::Sys::BossUploadDataMaker::getSessionID()) + ".txt";

		for (const auto& logReport: logReports) {
			std::string logEntry = 
				"Session ID: " + std::to_string(Lp::Sys::BossUploadDataMaker::getSessionID()) +
				" PID: " + std::to_string(logReport.pid) +
				" Permission Type: " + (logReport.isHost ? "Host" : "Client") +
				" Player Index: " + std::to_string(logReport.playerIdx) +
				" IP Address: " + formatIpBytes(logReport.ipAddress) +
				" Detection: " + nokrnl_DetectionType_strings.at(logReport.detectionType)
				+ "\n";

			log += logEntry;
		}

		Filesystem::writeFile("/vol/save/" + fileName, std::span<uint8_t>((uint8_t*)log.data(), (uint8_t*)log.data() + log.length()));
		*/
	}

	enum class QueueEvent {
		Death
	};

	static std::unordered_set<QueueEvent> queuedEvents[8] = {};

	namespace {
		void nokrnl_check_bombThrow(Game::Player::Player* player, float deltaTime) {
			NoKrnl::nokrnl_PlayerStatus& playerStatus = NoKrnl::nokrnl_playerStatuses[Game::Utl::getPlayerIdx(player)];

			if (
				(player->subWeaponId == SUB_SPLAT && player->playerInkAction->inkTank < 0.5 / 2.0) ||
				(player->subWeaponId == SUB_SUCTION && player->playerInkAction->inkTank < 0.7 / 2.0) ||
				(player->subWeaponId == SUB_BURST && player->playerInkAction->inkTank < 0.4 / 2.0) ||
				(player->subWeaponId == SUB_SEEKER && player->playerInkAction->inkTank < 0.8 / 2.0) ||
				(player->subWeaponId == SUB_SENSOR && player->playerInkAction->inkTank < 0.45 / 2.0) ||
				(player->subWeaponId == SUB_SPRINKLER && player->playerInkAction->inkTank < 0.6 / 2.0) ||
				(player->subWeaponId == SUB_BEAKON && player->playerInkAction->inkTank < 0.75 / 2.0) ||
				(player->subWeaponId == SUB_WALL && player->playerInkAction->inkTank < 0.6 / 2.0) ||
				(player->subWeaponId == SUB_DISRUPTOR && player->playerInkAction->inkTank < 0.5 / 2.0)
			) {
				playerStatus.addFlag(NoKrnl::nokrnl_DetectionType::InvalidInkTank);
			}

			if (deltaTime < 0.2) {
				playerStatus.addFlag(nokrnl_DetectionType::RapidFire);
			}
		}
	}

	static std::chrono::_V2::system_clock::time_point playerPrevUpdateTimes_Bullet[8][COMMON_EVENT_BUF_SIZE] = {};

	void nokrnl_check_host_data(Game::Player::Player* master) {
		NoKrnl::nokrnl_PlayerStatus& playerStatus = NoKrnl::nokrnl_playerStatuses[Game::Utl::getPlayerIdx(master)];

	}

	void nokrnl_check_equippedWeaponSet(Game::Player::Player* player) {
		NoKrnl::nokrnl_PlayerStatus& playerStatus = NoKrnl::nokrnl_playerStatuses[Game::Utl::getPlayerIdx(player)];

		nokrnl_WeaponSet playerWeaponSet = {
			static_cast<nokrnl_MainWeapon>(player->weaponId),
			static_cast<nokrnl_SubWeapon>(player->subWeaponId),
			static_cast<nokrnl_SpecialWeapon>(player->specialWeaponId),
		};

		if (playerWeaponSet.specialWeapon == nokrnl_SpecialWeapon::Rainmaker) playerStatus.addFlag(nokrnl_DetectionType::InvalidWeaponSet);

		for (auto& weaponSet : nokrnl_weaponSets) {
			if (playerWeaponSet == weaponSet) {
				return;
			}
		}

		playerStatus.addFlag(NoKrnl::nokrnl_DetectionType::InvalidWeaponSet);
	}

	void nokrnl_check_abilities(Game::Player::Player* player) {
		NoKrnl::nokrnl_PlayerStatus& playerStatus = NoKrnl::nokrnl_playerStatuses[Game::Utl::getPlayerIdx(player)];

		if (!player) return;
		if (!player->gearSkillMgr) return;

		std::vector<Cmn::Def::Ability> mainAbilities = Cmn::Def::getAbilitiesFromValue(player->gearSkillMgr->mainAbilityIds);

		std::vector<Cmn::Def::Ability> hatMainAbilities = { Cmn::Def::Ability::Tenacity, Cmn::Def::Ability::Comeback, Cmn::Def::Ability::LastDitchEffort, Cmn::Def::Ability::OpeningGambit };
		std::vector<Cmn::Def::Ability> clotheMainAbilities = { Cmn::Def::Ability::NinjaSquid, Cmn::Def::Ability::ColdBlooded, Cmn::Def::Ability::Recon, Cmn::Def::Ability::Haunt };
		std::vector<Cmn::Def::Ability> shoesMainAbilities = { Cmn::Def::Ability::InkResistanceUp, Cmn::Def::Ability::StealthJump, Cmn::Def::Ability::BombSniffer };

		for (const auto ability : mainAbilities) {
			if (Cmn::Def::mainAbilities.find(ability) == Cmn::Def::mainAbilities.end()) {
				continue;
			}

			if (
				std::count(hatMainAbilities.begin(), hatMainAbilities.end(), ability) > 1 ||
				std::count(clotheMainAbilities.begin(), clotheMainAbilities.end(), ability) > 1 ||
				std::count(shoesMainAbilities.begin(), shoesMainAbilities.end(), ability) > 1
			) {
				playerStatus.addFlag(nokrnl_DetectionType::InvalidAbilities);
			}
		}
	}
	
	void nokrnl_check_PacketBulletCloneEvent_expand(Game::BulletCloneEvent::BulletCloneEvent* cloneEvent, Game::Player::Player* player) {
		NoKrnl::nokrnl_PlayerStatus& playerStatus = NoKrnl::nokrnl_playerStatuses[Game::Utl::getPlayerIdx(player)];

		if (!cloneEvent) return;

		uint32_t playerIdx = Game::Utl::getPlayerIdx(player);

		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> timeDiff = now - playerPrevUpdateTimes_Bullet[playerIdx][cloneEvent->eventId];
		float deltaTime = timeDiff.count();

		std::optional<nokrnl_DetectionType> detectionType = {};

		float finalDeltaTime = deltaTime * playerStatus.averageDeltaTime;

		if (player->playerInkAction->inkTank <= 0.01) {
			playerStatus.consecutiveEmptyTankShots++;
		} else {
			playerStatus.consecutiveEmptyTankShots = 0;
		}

		if (playerStatus.consecutiveEmptyTankShots > 3) {
			playerStatus.addFlag(nokrnl_DetectionType::InvalidInkTank);
		}

		switch (cloneEvent->eventId) {
			case 0x65:
				nokrnl_check_bombThrow(player, deltaTime);
		}

		if (detectionType.has_value()) playerStatus.addFlag(detectionType.value());

		playerPrevUpdateTimes_Bullet[playerIdx][cloneEvent->eventId] = now;
	}
	
	static std::chrono::_V2::system_clock::time_point playerPrevUpdateTimes_Paint[8][COMMON_EVENT_BUF_SIZE] = {};

	void nokrnl_check_PacketPaintCloneEvent_expand(Game::PaintCloneEvent::PaintCloneEvent* cloneEvent, Game::Player::Player* player) {
		if (!cloneEvent) return;
		if (cloneEvent->eventId == 0) return;

		uint32_t playerIdx = Game::Utl::getPlayerIdx(player);

		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> timeDiff = now - playerPrevUpdateTimes_Paint[playerIdx][cloneEvent->eventId];
		float deltaTime = timeDiff.count();

		std::optional<nokrnl_DetectionType> detectionType = {};

		//CAFEINFO("Received paint event ID: " + std::to_string(cloneEvent->eventId));

		/*
		switch (cloneEvent->eventId) {
			case 0x65:
				ok = ok & nokrnl_check_bombThrow(player, deltaTime);
		}
		*/

		playerPrevUpdateTimes_Paint[playerIdx][cloneEvent->eventId] = now;
	}

	void nokrnl_check_RequestPaintArg(double paint, Game::Player::Player* player) {
		NoKrnl::nokrnl_PlayerStatus& playerStatus = NoKrnl::nokrnl_playerStatuses[Game::Utl::getPlayerIdx(player)];

		if (paint > 150.0) {
			CAFEINFO("Paint cheats detected for player " + std::to_string(Game::Utl::getPlayerIdx(player)));
			playerStatus.addMaxConfidenceFlag(NoKrnl::nokrnl_DetectionType::InstaCover);
		}
	}

	static std::chrono::_V2::system_clock::time_point playerPrevUpdateTimes_ReceiveState[8] = {};

	void nokrnl_check_Player_receiveState_Net(Game::Player::Player* player, Game::Player::Player prevPlayer) {
		NoKrnl::nokrnl_PlayerStatus& playerStatus = NoKrnl::nokrnl_playerStatuses[Game::Utl::getPlayerIdx(player)];

		static float highestHorizontalSpeed = 0.0;
		static float highestVerticalSpeed = 0.0;

		uint32_t playerIdx = Game::Utl::getPlayerIdx(player);

		auto playerPrevUpdateTime = playerPrevUpdateTimes_ReceiveState[playerIdx];
		auto now = std::chrono::high_resolution_clock::now();

		std::chrono::duration<float> timeDiff = now - playerPrevUpdateTime;
		float deltaTime = timeDiff.count();

		glm::vec2 horizontalMoveVec = {player->position.x, player->position.z};
		glm::vec2 prevHorizontalMoveVec = {prevPlayer.position.x, prevPlayer.position.z};

		float horizontalDist = glm::distance(horizontalMoveVec, prevHorizontalMoveVec);
		float verticalDist = std::abs(player->position.y - prevPlayer.position.y);

		float horizontalSpeed = horizontalDist / deltaTime;
		float verticalSpeed = horizontalDist / deltaTime;

		if (horizontalSpeed > 200.0) {
			playerStatus.addFlag(NoKrnl::nokrnl_DetectionType::BadMovement);
		}

		highestHorizontalSpeed = std::max(highestHorizontalSpeed, horizontalSpeed);
		highestVerticalSpeed = std::max(highestVerticalSpeed, verticalSpeed);

		//CAFEINFO("Highest horizontal speed: " + std::to_string(highestHorizontalSpeed));
		//CAFEINFO("Highest vertical speed: " + std::to_string(highestVerticalSpeed));

		playerPrevUpdateTimes_ReceiveState[playerIdx] = now;
	}

	void nokrnl_check_Player_handleDamageCalc(Game::Player::Player* sourcePlayer, Game::Player::Player* targetPlayer, double damage) {
		if (!sourcePlayer) return;
		if (!targetPlayer) return;
		if (!targetPlayer->playerDamage) return;

		CAFEINFO("Incoming damage from player " + std::to_string(Game::Utl::getPlayerIdx(sourcePlayer)) + " to player " + std::to_string(Game::Utl::getPlayerIdx(targetPlayer)));

		NoKrnl::nokrnl_PlayerStatus& sourcePlayerStatus = NoKrnl::nokrnl_playerStatuses[Game::Utl::getPlayerIdx(sourcePlayer)];

		if (!sourcePlayerStatus.eventStatus.alive) {
			//sourcePlayerStatus.addMaxConfidenceFlag(NoKrnl::nokrnl_DetectionType::GodMode);
			return;
		}

		NoKrnl::nokrnl_PlayerStatus& targetPlayerStatus = NoKrnl::nokrnl_playerStatuses[Game::Utl::getPlayerIdx(targetPlayer)];

		CAFEINFO("Received damage: " + std::to_string(damage));

		if (damage + targetPlayer->playerDamage->damageTaken > 1.0) {
			targetPlayerStatus.eventStatus.alive = false;
		}

		CAFEINFO("Player " + std::to_string(Game::Utl::getPlayerIdx(targetPlayer)) + " received damage from player " + std::to_string(Game::Utl::getPlayerIdx(sourcePlayer)));
	}

	void nokrnl_check_Player_receiveRevival_Net(Game::Player::Player* player) {
		NoKrnl::nokrnl_PlayerStatus& playerStatus = NoKrnl::nokrnl_playerStatuses[Game::Utl::getPlayerIdx(player)];

		auto now = std::chrono::high_resolution_clock::now();
		playerStatus.deathTime = now;
	}

	void nokrnl_check_Player_receiveDie_Net(Game::Player::Player* player) {
		NoKrnl::nokrnl_PlayerStatus& playerStatus = NoKrnl::nokrnl_playerStatuses[Game::Utl::getPlayerIdx(player)];

		if (playerStatus.deathTime.has_value()) {
			playerStatus.addFlag(nokrnl_DetectionType::FastRespawn);
		}

		auto now = std::chrono::high_resolution_clock::now();
		playerStatus.deathTime = now;
	}

	void reset() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < COMMON_EVENT_BUF_SIZE; j++) {
				playerPrevUpdateTimes_Bullet[i][j] = {};
			}
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < COMMON_EVENT_BUF_SIZE; j++) {
				playerPrevUpdateTimes_Paint[i][j] = {};
			}
		}
	}
}

static Game::Player::Player prevPlayers[8] = {};

static Game::Player::Player* eventPlayer = nullptr;

void nokrnl_repl_sendLog() {
	//int32_t stationsLength = nn::pia::transport::StationManager::s_pInstance->stationsLength;

	/*
	std::vector<int32_t> pids = {};

	for (int32_t stationIdx = 0; stationIdx < stationsLength; stationIdx++) {
		nn::pia::transport::StationConnectionInfo::StationConnectionInfo connInfo = {};
		nn::pia::transport::StationConnectionInfo::StationConnectionInfoCtor(&connInfo);

		nn::pia::transport::Station::Station* station = nn::pia::transport::StationManager::GetStation(nn::pia::transport::StationManager::s_pInstance, stationIdx);

		if ((uint32_t)station < 0x1B000000) {
			//CAFEINFO("Station #" + std::to_string(stationIdx) + " is NULL");
			continue;
		}

		nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo(nn::pia::transport::StationConnectionInfoTable::s_pInstance, station, &connInfo);

		pids.push_back(connInfo.stationLocation.principalId);
	}
	*/

	std::vector<NoKrnl::nokrnl_LogReportData> logReports = {};

	for (uint32_t i = 0; i < 8; i++) {
		NoKrnl::nokrnl_PlayerStatus* playerStatus = &NoKrnl::nokrnl_playerStatuses[i];

		if (!playerStatus) continue;
		if (!playerStatus->isOfficiallyFlagged()) continue;

		NoKrnl::nokrnl_LogReportData reportLog = {
			.flags = playerStatus->flags,
			.playerInfo = playerStatus->netStatus.playerInfo,
			.playerIdx = i,
			.pid = playerStatus->netStatus.pid,
			.ipAddress = playerStatus->netStatus.address.address,
			.isHost = false,
		};

		logReports.push_back(reportLog);
	}

	void* state = SLInternalNetGetState();

	if (state) {
		if (!logReports.empty()) NoKrnl::nokrnl_saveLogReports(state, logReports);
		else {
			CAFEINFO("logReports is NULL");
		}
	} else {
		CAFEINFO("State is NULL");
	}

	NoKrnl::reset();
}

void nokrnl_repl_Player_unpackState_Net(Game::Player::Player* _this, Game::PlayerNetState::PlayerNetState* netState, uint32_t unk) {
	eventPlayer = _this;
	Game::Player::unpackState_Net(_this, netState, unk);
	eventPlayer = _this;

	/*
	int32_t masterPid = Lp::Net::getMasterUniqueID();
	Game::Player::Player* master = nullptr;

	for (const auto player : Game::Utl::getAllPlayers()) {
		if (player->info->pid == masterPid) {
			master = player;
			break;
		}
	}

	if (master) {
		NoKrnl::nokrnl_check_host_data(master);
	}
	*/

	uint32_t playerIdx = Game::Utl::getPlayerIdx(_this);

	NoKrnl::nokrnl_PlayerStatus* playerStatus = &NoKrnl::nokrnl_playerStatuses[playerIdx];

	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> timeDiff = now - playerStatus->prevUpdateTime;
	float deltaTime = timeDiff.count();
	playerStatus->averageDeltaTime = (playerStatus->averageDeltaTime * SMOOTHING) + (deltaTime * (1.0f - SMOOTHING));

	playerStatus->prevUpdateTime = now;

	if (playerStatus->pingCount < MIN_PING_COUNT) {
		playerStatus->pingCount++;
		return;
	}

	if (Game::Player::isInMatchIntro(_this)) return;

	NoKrnl::nokrnl_check_equippedWeaponSet(eventPlayer);
	NoKrnl::nokrnl_check_abilities(eventPlayer);
}

void nokrnl_repl_BulletCloneHandle_receive(Game::BulletCloneHandle::BulletCloneHandle* _this, Game::Player::Player* player, int32_t cloneHandleIdx) {
	eventPlayer = player;
	Game::BulletCloneHandle::receive(_this, player, cloneHandleIdx);
	eventPlayer = nullptr;

	return;
}

void nokrnl_repl_PacketBulletCloneEvent_expand(Game::PacketBulletCloneEvent::PacketBulletCloneEvent* _this, Game::BulletCloneEvent::BulletCloneEvent* cloneEvent) {
	Game::PacketBulletCloneEvent::expand(_this, cloneEvent);

	if (!eventPlayer) return;

	uint32_t playerIdx = Game::Utl::getPlayerIdx(eventPlayer);
	NoKrnl::nokrnl_PlayerStatus* playerStatus = &NoKrnl::nokrnl_playerStatuses[playerIdx];

	if (playerStatus->pingCount < MIN_PING_COUNT) return;
	NoKrnl::nokrnl_check_PacketBulletCloneEvent_expand(cloneEvent, eventPlayer);

	//if (detectionType.has_value()) cloneEvent->eventId = -1;
	//if (detectionType.has_value()) playerStatus->detectionType = NoKrnl::nokrnl_check_PacketBulletCloneEvent_expand(cloneEvent, eventPlayer);
}

void nokrnl_repl_PaintCloneHandle_receive(Game::PaintCloneHandle::PaintCloneHandle* _this, Game::Player::Player* player, int32_t cloneHandleIdx) {
	eventPlayer = player;
	Game::PaintCloneHandle::receive(_this, player, cloneHandleIdx);
	eventPlayer = nullptr;
}

void nokrnl_repl_PacketPaintCloneEvent_expand(Game::PacketPaintCloneEvent::PacketPaintCloneEvent* _this, Game::PaintCloneEvent::PaintCloneEvent* cloneEvent) {
	Game::PacketPaintCloneEvent::expand(_this, cloneEvent);

	uint32_t playerIdx = Game::Utl::getPlayerIdx(eventPlayer);
	NoKrnl::nokrnl_PlayerStatus* playerStatus = &NoKrnl::nokrnl_playerStatuses[playerIdx];
}

void nokrnl_repl_Player_receiveState_Net(Game::Player::Player* _this, Game::PlayerNetState::PlayerNetState* playerNetState, uint32_t state) {
	Game::PlayerNetControl::receiveData(_this->playerNetControl, playerNetState, state);
	
	uint32_t playerIdx = Game::Utl::getPlayerIdx(_this);
	NoKrnl::nokrnl_PlayerStatus& playerStatus = NoKrnl::nokrnl_playerStatuses[playerIdx];
	NoKrnl::nokrnl_check_Player_receiveState_Net(_this, prevPlayers[playerIdx]);

	prevPlayers[playerIdx] = *_this;
}

void nokrnl_repl_Player_firstCalc(Game::Player::Player* _this) {
	Game::Player::firstCalc(_this);

	//uint32_t playerIdx = Game::Utl::getPlayerIdx(_this);
	//prevPlayers[playerIdx] = *_this;
}

int32_t nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo(nn::pia::transport::StationConnectionInfoTable::StationConnectionInfoTable* _this, nn::pia::transport::Station::Station* station, nn::pia::transport::StationConnectionInfo::StationConnectionInfo* connInfo) {
	return nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo(_this, station, connInfo);
}

void nokrnl_repl_IDManager_FUN_0215c8cc(enl::IDManager::IDManager* _this, int32_t unk) {
	enl::IDManager::FUN_0215c8cc(_this, unk);

	if (!_this) return;

	if ((uint32_t)nn::pia::transport::StationConnectionInfoTable::s_pInstance < 0x1B000000 || (uint32_t)nn::pia::transport::StationManager::s_pInstance < 0x1B000000) return;

	int32_t stationsLength = nn::pia::transport::StationManager::s_pInstance->stationsLength;

	for (int32_t stationIdx = 0; stationIdx < stationsLength; stationIdx++) {
		nn::pia::transport::StationConnectionInfo::StationConnectionInfo connInfo = {};
		nn::pia::transport::StationConnectionInfo::StationConnectionInfoCtor(&connInfo);

		nn::pia::transport::Station::Station* station = nn::pia::transport::StationManager::GetStation(nn::pia::transport::StationManager::s_pInstance, stationIdx);

		if ((uint32_t)station < 0x10000000) {
			//CAFEINFO("Station #" + std::to_string(stationIdx) + " is NULL");
			continue;
		}

		nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo(nn::pia::transport::StationConnectionInfoTable::s_pInstance, station, &connInfo);

		int32_t pid = connInfo.stationLocation.principalId;

		enl::UniqueID uuid = enl::UniqueID {
			.pid = pid,
			.unk = 0,
		};
		enl::UniqueID* uuidPtr = &uuid;

		enl::IDManager::IDManager* targetPlayerIdManager = enl::IDManager::getIDInfoByUniqueID(_this, uuidPtr);

		if ((uint32_t)targetPlayerIdManager < 0x10000000) {
			const void * address = static_cast<const void*>(targetPlayerIdManager);
			std::stringstream ss;
			ss << address;  
			std::string name = ss.str(); 

			CAFEINFO("Station #" + std::to_string(stationIdx) + " ID manager is NULL (" + name + ")");

			return;
		}

		uint32_t playerIdx = targetPlayerIdManager->playerID;

		if (playerIdx > 7 || playerIdx < 0) {
			CAFEWARNING("Player index \"" + std::to_string(playerIdx) + "\" is invalid.");
			continue;
		}

		NoKrnl::nokrnl_PlayerStatus* playerStatus = &NoKrnl::nokrnl_playerStatuses[playerIdx];
		playerStatus->netStatus.pid = connInfo.stationLocation.principalId;
		playerStatus->netStatus.address = connInfo.stationLocation.stationAddress.inetAddress;
		
		CAFEINFO("Received data from " + formatIpBytes(connInfo.stationLocation.stationAddress.inetAddress.address) + ":" + std::to_string(connInfo.stationLocation.stationAddress.inetAddress.port));

		uuid = enl::UniqueID {
			.pid = pid,
			.unk = 0,
		};
		uuidPtr = &uuid;

		if (!enl::IDManager::isConnected(_this, uuidPtr)) {
			CAFEINFO("Station #" + std::to_string(stationIdx) + " is not connected");
			continue;
		}

		if (playerStatus->isOfficiallyFlagged()) {
			enl::IDManager::disconnectStationInfo(_this, uuidPtr);

			if (nn::pia::session::Mesh::IsValidStationIndex(nn::pia::session::Mesh::s_pMesh, stationIdx)) {
				nn::pia::session::Mesh::UnfixDisconnectedId(nn::pia::session::Mesh::s_pMesh, stationIdx);
			}
		}
	}
}

double nokrnl_repl_Player_handleDamageCalc(Game::Player::Player** targetPlayerPtr, double damage, Game::Clone::Clone* clone, float* knockback) {
	if (targetPlayerPtr) {
		if (eventPlayer == *targetPlayerPtr) {
			CAFEINFO("Event player is equal to the target player so the source player is the local player");
			NoKrnl::nokrnl_check_Player_handleDamageCalc(Game::Player::localInstance, *targetPlayerPtr, damage);
		} else {
			NoKrnl::nokrnl_check_Player_handleDamageCalc(eventPlayer, *targetPlayerPtr, damage);
		}
	}

	return Game::Player::handleDamageCalc(targetPlayerPtr, damage, clone, knockback);
}

void nokrnl_repl_Player_receiveDie_Net(Game::Player::Player* _this, uint32_t param_1, glm::vec3 param_2, int32_t param_3, int32_t param_4) {
	uint32_t playerIdx = Game::Utl::getPlayerIdx(eventPlayer);
	NoKrnl::nokrnl_PlayerStatus& playerStatus = NoKrnl::nokrnl_playerStatuses[playerIdx];
	NoKrnl::nokrnl_check_Player_receiveDie_Net(_this);

	Game::Player::receiveDie_Net(_this, param_1, param_2, param_3, param_4);
}

int32_t nokrnl_repl_Socket_SendTo(nn::pia::common::Socket::Socket* _this, int32_t param_1, int32_t param_2, nn::pia::common::InetAddress::InetAddress* ipAddress, int32_t* param_4) {
	if (ipAddress) {
		//CAFEINFO("Received data from " + formatIpBytes(ipAddress->address) + ":" + std::to_string(ipAddress->port));
	}

	/*
	if (ipAddress) {
		CAFEINFO("SendTo IP address: " + formatIpBytes(ipAddress->address));
		for (const auto& playerStatus : nokrnl_playerStatuses) {
			if (ipAddress->address == playerStatus.netStatus.ipAddress && playerStatus.isOfficiallyFlagged() && ipAddress->address > 0) {
				CAFEINFO("Packet to destination " + formatIpBytes(ipAddress->address) + " rejected");
				return 0;
			}
		}
	}
	*/

	return nn::pia::common::Socket::SendTo(_this, param_1, param_2, ipAddress, param_4);
}

int32_t nokrnl_repl_Socket_RecvFrom(nn::pia::common::Socket::Socket* _this, int32_t param_1, int32_t param_2, nn::pia::common::InetAddress::InetAddress* ipAddress, int32_t param_4, int32_t* param_5) {
	if (ipAddress) {
		//CAFEINFO("Sending data to " + formatIpBytes(ipAddress->address) + ":" + std::to_string(ipAddress->port));
	}

	int32_t result = nn::pia::common::Socket::RecvFrom(_this, param_1, param_2, ipAddress, param_4, param_5);

	/*
	if (ipAddress) {
		CAFEINFO("RecvFrom IP address: " + formatIpBytes(ipAddress->address));
		for (int i = 0; i < 8; i++) {
			NoKrnl::nokrnl_PlayerStatus* playerStatus = &nokrnl_playerStatuses[i];

			if (!playerStatus) continue;

			if (playerStatus->netStatus.ipAddress != 0) {
				CAFEINFO("Player IP address: " + formatIpBytes(playerStatus->netStatus.ipAddress));
			}

			if (ipAddress->address == playerStatus->netStatus.ipAddress && playerStatus->isOfficiallyFlagged() && ipAddress->address > 0 && playerStatus->rejectCount < 500) {
				CAFEINFO("Packet from source " + formatIpBytes(ipAddress->address) + " rejected");
				ipAddress->address = 0;
				playerStatus->rejectCount++;
				return 0;
			}
		}
	}
	*/

	return result;
}

int32_t nokrnl_repl_RequestPaintArg_RequestPaintArg(int32_t _this, double paint, double param_2, int32_t param_3, int32_t param_4, int32_t param_5, int32_t param_6, int32_t param_7, int32_t param_8, int32_t param_9, byte param_10, int32_t param_11, int32_t param_12) {
	uint32_t playerIdx = Game::Utl::getPlayerIdx(eventPlayer);
	NoKrnl::nokrnl_PlayerStatus& playerStatus = NoKrnl::nokrnl_playerStatuses[playerIdx];
	NoKrnl::nokrnl_check_RequestPaintArg(paint, eventPlayer);

	CAFEINFO("paint: " + std::to_string(paint) + " param_2: " + std::to_string(param_2) + " param_3: " + std::to_string(param_3) + " param_4: " + std::to_string(param_4) + " param_5: " + std::to_string(param_5) + " param_6: " + std::to_string(param_6) + " param_7" + std::to_string(param_7) + " param_8: " + std::to_string(param_8) + " param_9: " + std::to_string(param_9) + " param_10: " + std::to_string(param_10) + " param_11: " + std::to_string(param_11) + " param_12: " + std::to_string(param_12));

	return Game::RequestPaintArg::ctor(_this, paint, param_2, param_3, param_4, param_5, param_6, param_7, param_8, param_9, param_10, param_11, param_12);
}

namespace Modules {
    NoKrnlHook::NoKrnlHook() {
		this->patch = {
			{0x0275b2dc, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_sendLog, 0x0275b2dc), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) 0x0200af90, 0x0275b2dc))},

			{0x026cb4cc, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_Player_unpackState_Net, 0x026cb4cc), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::Player::unpackState_Net, 0x026cb4cc))},

			{0x0266ed80, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_PaintCloneHandle_receive, 0x0266ed80), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::PaintCloneHandle::receive, 0x0266ed80))},
			{0x0266ed70, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_BulletCloneHandle_receive, 0x0266ed70), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::BulletCloneHandle::receive, 0x0266ed70))},

			{0x0266c7e8, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_PacketBulletCloneEvent_expand, 0x0266c7e8), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::PacketBulletCloneEvent::expand, 0x0266c7e8))},
			{0x0266c028, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_PacketPaintCloneEvent_expand, 0x0266c028), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::PacketPaintCloneEvent::expand, 0x0266c028))},

			{0x0266ee64, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_Player_receiveState_Net, 0x0266ee64), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::Player::receiveState_Net, 0x0266ee64))},
			{0x0266eea4, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_Player_receiveState_Net, 0x0266eea4), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::Player::receiveState_Net, 0x0266eea4))},

			{0x0267e68c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_Player_handleDamageCalc, 0x0267e68c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::Player::handleDamageCalc, 0x0267e68c))},

			{0x02c53d0c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02c53d0c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02c53d0c))},
			{0x02c8c848, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02c8c848), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02c8c848))},
			{0x02c8db08, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02c8db08), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02c8db08))},
			{0x02c8e87c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02c8e87c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02c8e87c))},
			{0x02c91fac, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02c91fac), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02c91fac))},
			{0x02c93654, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02c93654), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02c93654))},
			{0x02c948dc, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02c948dc), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02c948dc))},
			{0x02c9585c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02c9585c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02c9585c))},
			{0x02c958ac, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02c958ac), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02c958ac))},
			{0x02c96ddc, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02c96ddc), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02c96ddc))},
			{0x02c96f80, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02c96f80), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02c96f80))},
			{0x02c97458, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02c97458), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02c97458))},
			{0x02cbb23c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02cbb23c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02cbb23c))},
			{0x02cc0f70, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02cc0f70), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02cc0f70))},
			{0x02cc3b8c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02cc3b8c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02cc3b8c))},
			{0x02cc3e34, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_StationConnectionInfoTable_GetStationConnectionInfo, 0x02cc3e34), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::transport::StationConnectionInfoTable::GetStationConnectionInfo, 0x02cc3e34))},

			{0x0215e33c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_IDManager_FUN_0215c8cc, 0x0215e33c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) enl::IDManager::FUN_0215c8cc, 0x0215e33c))},
			{0x0215e610, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_IDManager_FUN_0215c8cc, 0x0215e610), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) enl::IDManager::FUN_0215c8cc, 0x0215e610))},
			{0x02160f78, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_IDManager_FUN_0215c8cc, 0x02160f78), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) enl::IDManager::FUN_0215c8cc, 0x02160f78))},

			// SendTo
            {0x02c4a038, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_Socket_SendTo, 0x02c4a038), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::common::Socket::SendTo, 0x02c4a038))},
            {0x02c4be14, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_Socket_SendTo, 0x02c4be14), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::common::Socket::SendTo, 0x02c4be14))},

			// RecvFrom
            {0x02c499f0, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_Socket_RecvFrom, 0x02c499f0), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nn::pia::common::Socket::RecvFrom, 0x02c499f0))},

            {0x0266c160, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_RequestPaintArg_RequestPaintArg, 0x0266c160), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::RequestPaintArg::ctor, 0x0266c160))},
            {0x0266c22c, PatchElement(DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) nokrnl_repl_RequestPaintArg_RequestPaintArg, 0x0266c22c), DynamicBranchReplacementSingle(BranchType::BranchLink, (void*) Game::RequestPaintArg::ctor, 0x0266c22c))},

            {0x100e9740, PatchElement((void*) nokrnl_repl_Player_firstCalc, (void*) Game::Player::firstCalc)},
		};

		this->enablePatch();
    }

	bool NoKrnlHook::allowDisable() {
		return silverlightInstance->m_currentlyInPublicMatch ? false : true;
	}
    
    bool NoKrnlHook::isCheatModule() {
        return false;
    }

    REGISTERVCLASS(NoKrnlHook)
}
