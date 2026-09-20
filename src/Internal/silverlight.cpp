#include "silverlight.h"
#include "Logic/controller.h"
#include "Logic/cheatcodes.h"
#include "Shared/Core/Logging.h"
#include<Internal/drm.h>

#include <coreinit/dynload.h>
#include<Internal/Menus/DirectoryMenu.h>
#include<numbers>
#include<cmath>
#include<Shared/colorconvert.h>
#include "Game/Assembler/ppcAssembler.h"
#include<coreinit/memory.h>
#include <nn/swkbd/swkbd_cpp.h>
#include <proc_ui/procui.h>

#include "Internal/Logic/Modules/suicide.h"
#include "Internal/Logic/Modules/flipteam.h"
#include "Internal/Logic/Modules/forcestart.h"
#include "Internal/Logic/Modules/namechanger.h"
#include "Internal/Logic/Modules/mapforce.h"
#include "Internal/Logic/Modules/displaymessage.h"
#include "Internal/Logic/Modules/memtools.h"
#include "Internal/Logic/Modules/switchscene.h"
#include "Internal/Logic/Modules/disableallcheats.h"
#include "Internal/Logic/Modules/pausegame.h"
#include "Internal/Logic/Modules/customweapon.h"
#include "Internal/Logic/Modules/save.h"
#include "Internal/Logic/Modules/customizetransition.h"
#include "Internal/Logic/Modules/forcegamemode.h"
#include "Internal/Logic/Modules/changeskybox.h"
#include "Internal/Logic/Modules/endgame.h"
#include "Internal/Logic/Modules/resetink.h"
#include "Internal/Logic/Modules/teleport.h"
#include "Internal/Logic/Modules/showfloor.h"
#include "Internal/Logic/Modules/disconnect.h"

#include "Internal/Logic/Modules/weaponchanger.h"
#include<Game/Filetypes/Helpers/Filesystem.h>

#include "Shared/Cafe/vpad.h"

#include "Internal/Logic/cheatcheck.h"

#include "Game/SysInit.h"
#include "Game/Net.h"

#include <coreinit/exit.h>

#include "Internal/Logic/Modules/colorcorrectionhook.h"

#include "Logic/save.h"

#include "Game/Sys.h"

#include "Game/Cnet/Cnet.h"

#include "Internal/Draw/rendering.h"

int rpl_entry(OSDynLoad_Module module, OSDynLoad_EntryReason reason) {
    return 0;
}

[[deprecated("Implement patches normally using the module system instead.")]]
void patch(uint32_t address, std::string instruction) {
    PPCAssemblerInOut res = {};
    ppcAssembler_assembleSingleInstruction(instruction.c_str(), &res);
    memcpy((void *) address, res.outputData.data(), 4);
}

// TODO: make all of the patches initial patch modules instead of using patch()
void initialPatches() {
    //Disable memory box patch
    patch(0x028b06c8, "nop");

    //PB with 1 player
    patch(0x02175B90, "nop");
    patch(0x02092C54, "nop");
    patch(0x028294B8, "nop");
    *(uint32_t *) 0x10031240 = 0x021F8818;
}

Silverlight::Silverlight() {
    silverlightInstance = std::unique_ptr<Silverlight>(this);
    Log::Init();


    //Intialize swkbd

    initialPatches();

    //Initialize Menus
    std::shared_ptr<Menus::DirectoryMenu> menu = std::make_shared<Menus::DirectoryMenu>();
    std::shared_ptr<Menus::DirectoryMenu> movementMenu = std::make_shared<Menus::DirectoryMenu>();
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Movement", movementMenu));


    m_topLevelMenu = menu;

    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Future Fly", "FutureFly"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("BHop", "BHop"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Swim Anywhere", "SwimAnywhere"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Stalk Player", "StalkPlayer"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Hijack Player Control", "HijackControl"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Always Movable", "AlwaysMovableWrapper"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Jump Mid-air", "JumpMidair"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Noclip Everywhere", "NoclipEverywhereWrapper"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Noclip Through Players", "NoclipThroughPlayers"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Anti Slippery Effect", "AntiSlipperyEffect"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Shoot While Superjumping", "ShootWhileSuperjumping"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Substrafe Fix", "SubStrafeFix"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Squid Roll", "SquidRoll"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Squid Surge", "SquidSurge"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("No Player Hitbox Collision", "NoPlayerHitboxCollision"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Low Gravity", "LowGravity"));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Improved Wall Paint",
                                                     "ImprovedWallPaint"));

    std::shared_ptr<Menus::DirectoryMenu> teleportMenu = std::make_shared<Menus::DirectoryMenu>();
    teleportMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    teleportMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Teleport Position", Modules::setTeleportPos));
    teleportMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Teleport", Modules::goToTeleportPos));
    movementMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("Teleport", teleportMenu));

    std::shared_ptr<Menus::DirectoryMenu> playerMenu = std::make_shared<Menus::DirectoryMenu>();
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Player", playerMenu));

    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Aim Assist", "AimAssist"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Aimbot", "AimBotWrapper"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Anti-Deathzone", "AntiDeathZone"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Player ESP", "PlayerEsp"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Tacticooler", "Tacticooler"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Infinite Ink", "InfiniteInk"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("No Auto Camera Movement", "NoAutoCameraMovement"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Sticky Camera", "StickyCamera"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("God Mode", "GodMode"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Scaffold", "Scaffold"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Disable Spawn Barrier", "DisableSpawnBarrier"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Insta Cover", "InstaCover"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Small Inkling", "SmallInkling"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("All Teammates Invincible", "AllTeammatesInvinciblePatch"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Anti Enemy Ink Effect", "AntiEnemyInkEffect"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Anti-KB", "AntiKB"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("See Enemy Signals", "SeeEnemySignals"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Signals Always Enabled", "SignalsAlwaysEnabled"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Spam Booyah Signal", "SpamBooyahSignal"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Spam To Me Signal", "SpamToMeSignal"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Freecam", "FreecamWrapper"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Superjump With Rainmaker", "SuperjumpWithRainmaker"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Invisibility", "Invisibility"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Insta Respawn", "InstaRespawn"));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Suicide", Modules::suicide));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Flip Team", Modules::flipTeam));
    playerMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Edit Name", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::NameChanger>()->toggle();
            }));

    std::shared_ptr<Menus::DirectoryMenu> weaponsMenu = std::make_shared<Menus::DirectoryMenu>();
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Weapon", weaponsMenu));

    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("S/B Rapidfire",
                                                      "BlasterShooterRapidfire"));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Sub Rapidfire",
                                                      "SubWeaponRapidfire"));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Main Rapid Fire",
                                                      "MainWeaponRapidFire"));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Special Always Charged",
                                                      "SpecialAlwaysCharged"));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Disable Jump RNG",
                                                     "DisableJumpRNG"));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Special Always Active",
                                                      "SpecialAlwaysActive"));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Stop Calc",
                                                     "StopCalc"));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Sub Weapons Always Usable",
                                                     "SubWeaponsAlwaysUsable"));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Silent Splat Bombs",
                                                     "SilentSplatBombs"));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Friendly Fire",
                                                     "FriendlyFire"));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Splash Wall Fix",
                                                     "SplashWallFix"));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("No Air Charge Penalty",
                                                     "NoAirChargePenalty"));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Charge Hold",
                                                     "ChargeHoldWrapper"));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Force Weapon", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::WeaponChanger>()->toggle();
            }));

    std::shared_ptr<Menus::DirectoryMenu> mapMenu = std::make_shared<Menus::DirectoryMenu>();
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Map", mapMenu));
    mapMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    mapMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Map Id(PB)", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::MapForceInput>()->toggle();
            }));
    mapMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Force Map(PB)", "MapForce"));
    mapMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Reset Ink", Modules::resetInk));

    std::shared_ptr<Menus::DirectoryMenu> hudMenu = std::make_shared<Menus::DirectoryMenu>();
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("HUD", hudMenu));

    hudMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));

    hudMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Edit Display Message", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::DisplayMessageInput>()->toggle();
            }));

    hudMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Display Message",
                                                      "DisplayMessage"));
    std::shared_ptr<Menus::DirectoryMenu> antibansMenu = std::make_shared<Menus::DirectoryMenu>();
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Antibans", antibansMenu));
    antibansMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    antibansMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Zero Paint", "ZeroPaint"));
    antibansMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Anonymizer", "AnonymizerWrapper"));

    std::shared_ptr<Menus::DirectoryMenu> debugMenu = std::make_shared<Menus::DirectoryMenu>();
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Debug", debugMenu));
    debugMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    debugMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Load Bullets Everyone (PB only)", "LoadBulletsEverywhere"));
    debugMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("DebugMove", "DebugMove"));
    debugMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Enter ShowFloor", Modules::enterShowfloor));

    std::shared_ptr<Menus::DirectoryMenu> matchMenu = std::make_shared<Menus::DirectoryMenu>();
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Match", matchMenu));
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Force Start", Modules::forceStart));
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Disconnect", Modules::disconnect));
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Skip Intro", Modules::skipIntro));
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("End Game", Modules::endGame));
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Silverlight Matchmaking", "SilverlightMatchmaking"));
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Freeze Lobby Timer", "FreezeTimer"));
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Rainmaker Chaos", "RainmakerChaos"));
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Infinite Match Time (Ranked Modes Only)", "InfiniteTime"));
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Force Lag", "ForceLag"));
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Fast Internet", "FastInternetWrapper"));
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Force Networked Damage", "ForceNetworkedDamage"));
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Always Host New Lobby", "AlwaysHostNewLobby"));
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Gamemode", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::ForceGamemodeInput>()->toggle();
            }));
    matchMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Force Gamemode", "ForceGamemode"));

    std::shared_ptr<Menus::DirectoryMenu> bypassMenu = std::make_shared<Menus::DirectoryMenu>();
    bypassMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Bypass", bypassMenu));
    bypassMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Anti-MMR", "AntiMMR"));
    bypassMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("News Skip", "NewsSkip"));
    bypassMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Shop Bypass", "ShopBypass"));
    bypassMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Recon Timer Bypass", "ReconTimerBypass"));
    bypassMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Booyah Limit Bypass", "BooyahLimitBypass"));
    bypassMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Anti-DC", "AntiDC"));

    std::shared_ptr<Menus::DirectoryMenu> heroModMenu = std::make_shared<Menus::DirectoryMenu>();
    heroModMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Hero Mode", heroModMenu));
    heroModMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Infinite Lives", "InfiniteLives"));
    heroModMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Infinite Power Eggs", "InfinitePowerEggs"));


    std::shared_ptr<Menus::DirectoryMenu> environmentMenu = std::make_shared<Menus::DirectoryMenu>();
    environmentMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Environment", environmentMenu));
    environmentMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Splatfest Mode", "SplatfestModeWrapper"));

    std::shared_ptr<Menus::DirectoryMenu> cosmeticMenu = std::make_shared<Menus::DirectoryMenu>();
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Cosmetic", cosmeticMenu));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("No Ink Tank", "NoInkTank"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Disable Visible Gear", "DisableVisibleGear"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Bubbly Hair", "BubblyHair"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Rainbow Screen", "RainbowScreen"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("SRL Gear", "SRL"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Rainbow Ink", "RainbowInkWrapper"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Trail", "Trail"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Set Skybox", "ChangeSkyboxInput"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Change Skybox", "ChangeSkybox"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Emote", "EmoteWrapper"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Disable Death Effect", "DisableDeathEffect"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Disable Crosshair", "DisableShotGuide"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Disable Sub Line", "DisableSubLine"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Hide Low Ink Warning", "HideLowInkWarning"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Disable All Particles", "DisableAllParticles"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Shadows During Night", "ShadowsDuringNight"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Disable Player Shadows", "DisablePlayerShadows"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Disable Ink Tank Popup", "DisableInkTankPopup"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Hide Damage Overlay", "HideDamageOverlay"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Light Graphics Mode", "LightGfxMode"));

    std::shared_ptr<Menus::DirectoryMenu> customizeSkyboxMenu = std::make_shared<Menus::DirectoryMenu>();
    customizeSkyboxMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    customizeSkyboxMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Skybox", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::ChangeSkyboxInput>()->toggle();
            }));
    customizeSkyboxMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Custom Skybox", "ChangeSkybox"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("Change Skybox", customizeSkyboxMenu));

    std::shared_ptr<Menus::DirectoryMenu> customizeTransitionMenu = std::make_shared<Menus::DirectoryMenu>();
    customizeTransitionMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    customizeTransitionMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Transition", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::TransitionInput>()->toggle();
            }));
    customizeTransitionMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Custom Transition", "CustomizeTransition"));
    cosmeticMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("Customize Transition", customizeTransitionMenu));

    std::shared_ptr<Menus::DirectoryMenu> soundMenu = std::make_shared<Menus::DirectoryMenu>();
    soundMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Sound", soundMenu));
    soundMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Disable Battle Music", "DisableBattleMusic"));
    soundMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("BGM Echo", "BGMEcho"));

    std::shared_ptr<Menus::DirectoryMenu> memtoolsMenu = std::make_shared<Menus::DirectoryMenu>();
    memtoolsMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Memtools", memtoolsMenu));
    memtoolsMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Scan Bytes", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::SearchForBytesInput>()->toggle();
            }));

    std::shared_ptr<Menus::DirectoryMenu> guiMenu = std::make_shared<Menus::DirectoryMenu>();
    guiMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("GUI", guiMenu));
    guiMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Show FPS", "ShowFPS"));
    guiMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Show System Clock", "ShowClock"));
    guiMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Show HP", "ShowHP"));
    guiMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Photograph Mode", "PhotographModeWrapper"));
    guiMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Pause Menu Always Usable", "PauseMenuAlwaysUsable"));
    guiMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Photoshoot", "PhotoshootWrapper"));

    std::shared_ptr<Menus::DirectoryMenu> sceneMenu = std::make_shared<Menus::DirectoryMenu>();
    sceneMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    sceneMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Scene", []() {
                silverlightInstance->m_moduleStates.getUpdateModule("SceneNameInput")->toggle();
            }));
    sceneMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Map", []() {
                silverlightInstance->m_moduleStates.getUpdateModule("MapNameInput")->toggle();
            }));

    std::shared_ptr<Menus::DirectoryMenu> networkMenu = std::make_shared<Menus::DirectoryMenu>();
    networkMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Network", networkMenu));
    networkMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Packet Analyzer", "IPInspectionHook"));

    sceneMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Switch Scene", []() {
                switchScene(g_nextSceneId);
            }));
    menu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("Scene", sceneMenu));

    std::shared_ptr<Menus::DirectoryMenu> qolMenu = std::make_shared<Menus::DirectoryMenu>();
    qolMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("QoL", qolMenu));
    qolMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("DayChange To Lobby", "DayChangeToLobby"));
    qolMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Extended Leave Threshold", "ExtendedLeaveThreshold"));
    qolMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("SplatfestButton", "SplatfestButton"));
    qolMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Join Ranked Through Friends", "JoinRankedThroughFriends"));

    std::shared_ptr<Menus::DirectoryMenu> renderingMenu = std::make_shared<Menus::DirectoryMenu>();
    renderingMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Rendering", renderingMenu));
    renderingMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Obj Viewer", "ObjViewer"));
    renderingMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Plaza Players Always Visible", "PlazaPlayersAlwaysVisible"));

    std::shared_ptr<Menus::DirectoryMenu> challengesMenu = std::make_shared<Menus::DirectoryMenu>();
    challengesMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Challenges", challengesMenu));
    challengesMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("CPS Mode", "CPSMode"));
    challengesMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Splattercolor Screen Effect", "AntiVision"));

    std::shared_ptr<Menus::DirectoryMenu> controlsMenu = std::make_shared<Menus::DirectoryMenu>();
    controlsMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Controls", controlsMenu));
    controlsMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Jump With B Button", "JumpWithBButton"));

    std::shared_ptr<Menus::DirectoryMenu> gameMenu = std::make_shared<Menus::DirectoryMenu>();
    gameMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Game", gameMenu));
    gameMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Disable RNG Calc", "DisableRNGCalc"));

    std::shared_ptr<Menus::DirectoryMenu> customWeaponMenu = std::make_shared<Menus::DirectoryMenu>();
    customWeaponMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    customWeaponMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Main Weapon", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::MainWeapon>()->toggle();
            }));
    customWeaponMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Sub Weapon", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::SubWeapon>()->toggle();
            }));
    customWeaponMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Special Weapon", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::SpecialWeapon>()->toggle();
            }));
    customWeaponMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Custom Weapon", "CustomWeapon"));
    weaponsMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("Custom Weapon", customWeaponMenu));

    std::shared_ptr<Menus::DirectoryMenu> saveMenu = std::make_shared<Menus::DirectoryMenu>();
    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));

    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Level", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::CustomLevelInput>()->toggle();
            }));
    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Enable Custom Level", "CustomLevel"));

    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Level Exp", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::CustomLevelExpInput>()->toggle();
            }));
    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Enable Custom Level Exp", "CustomLevelExp"));

    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Rank", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::CustomRankInput>()->toggle();
            }));
    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Enable Custom Rank", "CustomRank"));

    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Rank Points", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::CustomRankPointsInput>()->toggle();
            }));
    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Enable Custom Rank Points", "CustomRankPoints"));

    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Money", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::CustomMoneyInput>()->toggle();
            }));
    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Enable Custom Money", "CustomMoney"));

    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Fest Rank", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::CustomFestRankInput>()->toggle();
            }));
    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Enable Custom Fest Rank", "CustomFestRank"));

    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Fest Rank Points", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::CustomFestRankPointsInput>()->toggle();
            }));
    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Enable Custom Fest Rank Points", "CustomFestRankPoints"));

    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Set Fest Team", []() {
                silverlightInstance->m_moduleStates.getModule<Modules::CustomFestTeamInput>()->toggle();
            }));
    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Enable Custom Fest Team", "CustomFestTeam"));
    saveMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("All Unlocked", "AllUnlocked"));

    menu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("Save", saveMenu));

	//menu->m_menuItems.push_back(
		//std::make_shared<Menus::UpdateModuleItem>("AI", "AIUpdate"));

	menu->m_menuItems.push_back(
		std::make_shared<Menus::PatchModuleItem>("NoKrnl", "NoKrnlHook"));

    std::shared_ptr<Menus::DirectoryMenu> languageMenu = std::make_shared<Menus::DirectoryMenu>();
    languageMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Language", languageMenu));
    languageMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Disable Localizations", "DisableLocalizations"));

    std::shared_ptr<Menus::DirectoryMenu> paintMenu = std::make_shared<Menus::DirectoryMenu>();
    paintMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Paint", paintMenu));
    paintMenu->m_menuItems.push_back(
            std::make_shared<Menus::PatchModuleItem>("Disable Death Paint", "DisableDeathPaint"));

    std::shared_ptr<Menus::DirectoryMenu> devMenu = std::make_shared<Menus::DirectoryMenu>();
    menu->m_menuItems.push_back(std::make_shared<Menus::SubdirectoryItem>("Dev", devMenu));
    devMenu->m_menuItems.push_back(
            std::make_shared<Menus::SubdirectoryItem>("..", menu));
    devMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("Player Debug Idx", "DbgPlayerInfoInput"));
    devMenu->m_menuItems.push_back(
            std::make_shared<Menus::UpdateModuleItem>("DbgPlayerInfo", "DbgPlayerInfoWrapper"));
    devMenu->m_menuItems.push_back(std::make_shared<Menus::ButtonItem>("Switch to LAN networking", []() -> void {
		uint32_t netType = 1;
		Lp::Utl::setNetworkingType(&netType);
    }));

    menu->m_menuItems.push_back(
            std::make_shared<Menus::ButtonItem>("Disable All Cheats", Modules::disableAllCheats));
    //menu->m_menuItems.push_back(
    //std::make_shared<Menus::ButtonItem>("Pause Game", Modules::pauseGame));
	
	menu->m_menuItems.push_back(std::make_shared<Menus::ButtonItem>("Save Module State", []() -> void {
        saveModules();
    }));

    menu->m_menuItems.push_back(std::make_shared<Menus::ButtonItem>("Disconnect", []() -> void {
	Cnet::NetErrorScreen::NetErrorScreen netErrorScreen;
	Cnet::NetErrorScreen::in(&netErrorScreen);
    }));
	
    menu->m_menuItems.push_back(std::make_shared<Menus::ButtonItem>("Quit Game", []() -> void {
	abort();
    }));

    m_menu = m_topLevelMenu;

    fetchBannedUsers();

    CAFEINFO("Initializing Silverlight!")
}

//Extra parameters due to requirements for text rendering
void Silverlight::update(uint32_t unk1, uint32_t unk2) {
    //Controller::cheatCodesCheck();

    CHEAT_CHECK

    silverlightInstance->m_generator.discard(1);

	// only runs once
    static bool _ = []() {
        nn::swkbd::CreateArg createArg;

        createArg.regionType = nn::swkbd::RegionType::Europe;
        createArg.workMemory = malloc(nn::swkbd::GetWorkMemorySize(0));
        createArg.fsClient = &Filesystem::g_fsClient;

        if (!nn::swkbd::Create(createArg)) {
            CAFEERRORSHOW("Unable to initialize software keyboard");
        }

        nn::swkbd::MuteAllSound(false);
        return true;
    }();

    CHEAT_CHECK

    MainMgr *mainMgr = g_playerMgr;
	Cmn::StaticMem::StaticMem *staticMem = getStaticMem();

	static bool first = true;

    if (mainMgr == nullptr || staticMem == nullptr) {
        m_renderer.updateVars((DebugTextRenderer *) unk1);
        m_renderer.setTextScale(3);
        m_renderer.setTextCursor({-600, -250});
        m_renderer.drawTextRainbow("Waiting for game\nto finish loading...");
        return;
    }

	if(first){
        first = false;
        loadModules();
    }

    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> timediff = now - m_lastUpdate;
    float deltaTime = timediff.count();

    Controller::controllerCheck(deltaTime);

    m_lastUpdate = now;

    m_moduleStates.execModules(deltaTime);

    m_renderer.updateVars((DebugTextRenderer *) unk1);

    CHEAT_CHECK

    draw(deltaTime);

}

void Silverlight::draw(float deltaTime) {
    CHEAT_CHECK

    if (m_drawMenu && !this->m_moduleStates.isInFocusedModuleMode) {
        m_renderer.drawTextRainbow("Silverlight Beta v0.4\n");
        m_menu->draw();
    }
}

/*
void allocHeap() {
    Lp::Sys::HeapGroup* heapGroup = Lp::Sys::HeapGroup::sInstance;

    if (heapGroup) {
        sead::ExpHeap* othersHeap = heapGroup->mHeaps[Lp::Sys::HeapGroup::Group::cOthers];
		sead::HeapMgr::setCurrentHeap_(sead::HeapMgr::sInstance, othersHeap);
        sead::Heap* currentHeap = sead::HeapMgr::getCurrentHeap(sead::HeapMgr::sInstance);

        if (!mSilverlightHeap) {
            sead::SafeStringBase<char> str;
            str.mCharPtr = (char*)"SilverlightHeap";

            mSilverlightHeap = sead::ExpHeap::create(0, str, currentHeap, 4, sead::Heap::HeapDirection::TAIL, true);
        }
    }
}
*/
