#pragma once
#include "../imgui/imgui.h"
#include "../../SDK/Imports.hpp"

namespace Settings {
	extern bool drawSkeleton;
	extern bool drawBox;
	extern bool drawCrosshair;
	extern bool drawHealthBar;
	extern bool drawName;
	extern bool drawSnapLine;
	extern bool drawSnaplines;
	extern bool freeze;
	extern bool niggerCross;

	extern bool thirdperson;

	extern bool speedhack;
	extern bool enableAimbot;

	extern float aimbotFov;
	extern bool crosshairScoped;
	extern int CrosshairLength;
	extern int CrosshairGap;
	extern int CrosshairThickness;
	extern float time;
	extern int speedHackkey;
	extern int aimbotKey;
	extern int jumpKey;
	extern int LongNeckKey;
	extern int flyKey;

	extern bool adminFlag;

	extern bool shootInAir;

	extern bool noRecoil;
	extern bool rapidFire;
	extern bool shootAnywhere;
	extern bool spiderClimb;
	extern bool infinateJump;
	extern bool instantCompound;

	extern bool enableSmoothing;
	extern float aimbotSmoothing;

	extern float FovSlider;

	extern bool enableCompensateRecoil;

	extern int boxDistance;
	extern int skeletonDistance;
	extern int healthDistance;
	extern int nameDistance;

	extern int typeBox;

	extern int fov_changer_key;

	extern float FiledVIEWW;

	extern const char* boxTypes[];

	extern const char* bones[];

	extern const char* oresItems[];

	extern bool selectedOres[8];

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