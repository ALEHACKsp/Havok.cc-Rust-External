#pragma once
#include "Settings.hpp"

namespace Settings {
	bool drawSkeleton = false;
	bool drawBox = false;
	bool drawCrosshair = false;
	bool niggerCross = false;
	bool drawHealthBar = false;
	bool healthNiggers = false;
	bool drawName = false;
	bool drawWeapon = false;
	bool drawSnaplines = false;

	bool enableAimbot = false;
	bool freeze = false;


	bool bradleyESP = true;
	bool shootAnywhere = false;
	bool noRecoil = false;
	bool noSpread = false;
	bool rapidFire = false;
	bool snapLinez = false;
	bool instantCompound = false;

	float aimbotFov = 10;

	float FiledVIEWW = 90;

	float rapidfirevalue = 0.01; //0.09

	bool enableSmoothing = false;
	float aimbotSmoothing = 10;

	bool enableCompensateRecoil = false;

	int boxDistance = 100;
	int weaponDistance = 100;
	int skeletonDistance = 100;
	int healthDistance = 100;
	int nameDistance = 100;

	float FovSlider = 10;

	int aimbotKey = 0;

	int jumpKey = 0;
	int LongNeckKey = 0;
	int flyKey = 0;
	int walkWaterKEY = 0;
	bool walkOnWater = false;

	int aimBone = 0;

	bool spiderClimb = false;
	bool corpseESP = false;

	bool flyHack = false;
	bool infinateJump = false;

	bool adminFlag = false;

	bool longhit;
	bool runhit;
	bool longmed;

	float time = 12.f;

	bool shootInAir = false;
	bool speedhack = false;
	int corpseESPdistance = 100;
	int speedHackkey = 0;
	bool thirdperson = false;

	bool fastSwitchWeapons = false;

	bool tapeoka = false;
	int fov;
	int fov_changer_key;

	int typeBox = 0;

	const char* boxTypes[] = { safe_str("Static Box"), safe_str("Corner Box"), safe_str("Filled Box") };

	const char* bones[]{ safe_str("Head"), safe_str("Chest"), safe_str("Pelvis"), safe_str("Penis") };

	const char* oresItems[]{ safe_str("Stone Ore"), safe_str("Sulfur Ore"), safe_str("Metal Ore"), safe_str("Hemp"), safe_str("Metal"), safe_str("Stone"), safe_str("Sulfur"), safe_str("Wood"), safe_str("Stash")};
	bool selectedOres[9]{ false, false, false, false, false, false, false, false, false };

	float drawColor_box[4] = { 1.f, 1.f, 1.f, 1.f };
	float drawColor_skeleton[4] = { 1.f, 1.f, 1.f, 1.f };
	float drawColor_crosshair[4] = { 1.f, 1.f, 1.f, 1.f };
	float drawColor_name[4] = { 1.f, 1.f, 1.f, 1.f };
	float drawColor_health[4] = { 1.f, 1.f, 1.f, 1.f };

	float drawColor_friendly[4] = { 0.332143, 0.779874, 0.2011, 1 };

	bool stoneESP = false;
	bool crosshairScoped = false;
	int CrosshairLength = 17;
	int CrosshairGap = 6;
	int CrosshairThickness = 1;

	bool metalOreESP = false;
	bool sulfurOreESP = false;
	bool stoneOreESP = false;

	bool patrolHeliESP = false;
	bool HempESP = false;



	bool day_changer = false;
	bool night_mode = false;
	bool sky_changer = false;
	float day_time = 12;
	float sky_color = 1;
	float cloud_color = 1;
	float cloud_brightness = 1;

	bool thickBullet = false;
}