#pragma once
#include "../imgui/imgui.h"
#include "../../SDK/Imports.hpp"

namespace Settings {
	//Aimbot:
	extern int aimbotHitbox;
	extern bool enableAimbot;
	extern float aimbotFov;
	extern int aimbotKey;
	extern float aimbotSmoothing;



	extern bool drawSkeleton;
	extern bool drawBox;
	extern bool drawCrosshair;
	extern bool drawHealthBar;
	extern bool drawName;
	extern bool drawSnapLine;
	extern bool healthNiggers;
	extern bool drawSnaplines;
	extern bool drawWeapon;
	extern bool freeze;
	extern bool niggerCross;
	extern bool corpseESP;
	extern bool snapLinez;

	extern bool longhit;
	extern bool runhit;
	extern bool longmed;

	extern bool thirdperson;

	extern bool speedhack;
	extern bool crosshairScoped;
	extern int CrosshairLength;
	extern int CrosshairGap;
	extern int CrosshairThickness;
	extern float time;
	extern int speedHackkey;
	extern int corpseESPdistance;
	extern int jumpKey;
	extern bool bradleyESP;
	extern int LongNeckKey;
	extern int flyKey;

	extern bool adminFlag;

	extern bool shootInAir;

	extern bool noRecoil;
	extern bool noSpread;
	extern bool rapidFire;
	extern bool shootAnywhere;
	extern bool spiderClimb;
	extern bool infinateJump;
	extern bool instantCompound;
	
	extern bool enableSmoothing;

	extern float FovSlider;

	extern bool enableCompensateRecoil;

	extern int boxDistance;
	extern int skeletonDistance;
	extern int healthDistance;
	extern int nameDistance;
	extern int weaponDistance;

	extern int typeBox;

	extern int fov_changer_key;

	extern float FiledVIEWW;

	extern const char* boxTypes[];

	extern const char* bones[];

	extern const char* oresItems[];

	extern bool selectedOres[9];

	extern float drawColor_box[4];
	extern float drawColor_skeleton[4];
	extern float drawColor_crosshair[4];
	extern float drawColor_name[4];
	extern float drawColor_health[4];

	extern float drawColor_friendly[4];

	extern bool fov_Changer;

	extern bool stoneESP;

	extern int aimBone;
	extern bool fastSwitchWeapons;

	extern bool metalOreESP;
	extern bool sulfurOreESP;
	extern bool stoneOreESP;

	extern bool patrolHeliESP;
	extern bool HempESP;
	extern bool walkOnWater;
	extern int walkWaterKEY;
	extern bool flyHack;
	extern bool tapeoka;
	extern float rapidfirevalue;

	extern bool day_changer;
	extern bool night_mode;
	extern float day_time;
	extern float sky_color;
	extern float cloud_color;
	extern float cloud_brightness;
	extern bool sky_changer;

	extern bool thickBullet;
};