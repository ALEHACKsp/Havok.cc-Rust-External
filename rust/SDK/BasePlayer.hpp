#pragma once

#pragma region Includes
#include "Imports.hpp"
#include "Driver.hpp"
#include "Utils.hpp"
#include "HeldItem.hpp"
#pragma endregion

#pragma region BPFlags

enum class BCameraMode {
	FirstPerson = 0,
	ThirdPerson = 1,
	Eyes = 2,
	FirstPersonWithArms = 3,
	Last = 3
};

enum class BPlayerFlags {
	Unused1 = 1,
	Unused2 = 2,
	IsAdmin = 4,
	ReceivingSnapshot = 8,
	Sleeping = 16,
	Spectating = 32,
	Wounded = 64,
	IsDeveloper = 128,
	Connected = 256,
	ThirdPersonViewmode = 1024,
	EyesViewmode = 2048,
	ChatMute = 4096,
	NoSprint = 8192,
	Aiming = 16384,
	DisplaySash = 32768,
	Relaxed = 65536,
	SafeZone = 131072,
	ServerFall = 262144,
	Workbench1 = 1048576,
	Workbench2 = 2097152,
	Workbench3 = 4194304
};

enum class BMapNoteType {
	Death = 0,
	PointOfInterest = 1
};

enum class BTimeCategory {
	Wilderness = 1,
	Monument = 2,
	Base = 4,
	Flying = 8,
	Boating = 16,
	Swimming = 32,
	Driving = 64
};

#pragma endregion



#pragma region OffsetStuff

#define ConVar_Graphics_c 0x3231F60

#pragma endregion




#pragma region BList

enum BonesList : int
{
	r_foot = 3,
	l_knee = 2,
	l_hip = 1,
	l_foot = 15,
	r_knee = 14,
	r_hip = 13,
	spine1 = 18,
	neck = 46,
	head = 47,
	l_upperarm = 24,
	l_forearm = 25,
	l_hand = 26,
	r_upperarm = 55,
	r_forearm = 56,
	r_hand = 57
};

#pragma endregion

#pragma region MSFlags

enum class MStateFlags {
	Ducked = 1,
	Jumped = 2,
	OnGround = 4,
	Sleeping = 8,
	Sprinting = 16,
	OnLadder = 32,
	Flying = 64,
	Aiming = 128,
	Prone = 256,
	Mounted = 512,
	Relaxed = 1024,
};

#pragma endregion

#pragma region BPClass

class BasePlayer {
public:

	BasePlayer() {}

	BasePlayer(uintptr_t _ent, uintptr_t _trans, uintptr_t _obj) {

		this->player = Read<uintptr_t>(_ent + 0x28); //Entity
		this->visualState = Read<uintptr_t>(_trans + 0x38);

		this->playerFlags = Read<int32_t>(_ent + 0x650); //public BasePlayer.PlayerFlags playerFlags;
		this->name = ReadNative(_obj + 0x60);

		this->playerModel = Read<uintptr_t>(this->player + 0x4C0); //BasePlayer -> public PlayerModel playerModel;
		this->modelState = Read<uintptr_t>(this->player + 0x5E0); //0x588 // public ModelState modelState;

		this->position = Read<Vector3>(this->visualState + 0x90); //internal Vector3 position;
		this->health = Read<float>(this->player + 0x224);//private float _health;
	}

public:


	void setViewAngles(Vector3 angles) { // vector 3
		Write<Vector3>(Read<uint64_t>(this->player + 0x4E0) + 0x3C, angles); //public PlayerInput input; | private Vector3 bodyAngles;
	}

	void setViewAngles(Vector2 angles) { // vector 2
		Write<Vector2>(Read<uint64_t>(this->player + 0x4E0) + 0x3C, angles); //public PlayerInput input; | private Vector3 bodyAngles;
	}

	void setPlayerFlag(BPlayerFlags flag) {
		Write(this->player + 0x650, flag); //0x5F8 //public BasePlayer.PlayerFlags playerFlags;
	}

	void setModelFlag(MStateFlags flag) {
		Write(this->modelState + 0x24, flag);
	}

public:

	bool IsInView() {
		Vector2 screen_pos;
		if (!Utils::WorldToScreen(this->getPosition(), screen_pos))
			return false;

		return true;
	}


	bool isLocalPlayer() {
		return Read<bool>(this->playerModel + 0x279); //internal bool isLocalPlayer;
	}



	bool isSameTeam(std::unique_ptr<BasePlayer>& localPlayer) {
		auto localTeam = Read<uint32_t>(localPlayer->player + 0x590);//public PlayerTeam clientTeam;
		auto playerTeam = Read<uint32_t>(this->player + 0x590); //0x580

		if (localTeam == 0 || playerTeam == 0)
			return false;

		return (localTeam == playerTeam);
	}

	bool isConnected() {
		return this->getPlayerFlag(BPlayerFlags::Connected);
	}

	bool isSleeping() {
		return this->getPlayerFlag(BPlayerFlags::Sleeping);
	}

	bool isWounded() {
		return this->getPlayerFlag(BPlayerFlags::Wounded);
	}

	bool isAiming() {
		return this->getPlayerFlag(BPlayerFlags::Aiming);
	}

	bool isFrozen() {
		if (GetAsyncKeyState(Settings::flyKey))
		{
			return Read<bool>(this->player + 0x4C8); //public bool Frozen;
		}
	}

	bool isDead() {
		return (this->health <= 0);
	}

public:

	uint64_t getUserID()
	{
		return Read<uint64_t>(this->player + 0x698); //public ulong userID;
	}

	int getDistance(std::unique_ptr<BasePlayer>& player) {
		return this->getPosition().Distance(player->position);
	}

	std::string getDistanceStr(std::unique_ptr<BasePlayer>& player) {
		return std::to_string(this->getDistance(player));
	}

	uint64_t getMountedEntity() {
		return Read<uint64_t>(this->player + 0x590);
	}

	bool getModelFlag(MStateFlags flag) {
		return (this->playerModel & static_cast<int32_t>(flag)) == static_cast<int32_t>(flag);
	}

	bool getPlayerFlag(BPlayerFlags flag) {
		return (this->playerFlags & static_cast<int32_t>(flag)) == static_cast<int32_t>(flag);
	}

	std::string getASCIIName(std::wstring name) {
		return std::string(name.begin(), name.end());
	}

	Vector3 getVelocity() {
		return Read<Vector3>(this->playerModel + 0x21C); //private Vector3 newVelocity;
	}

	Vector3 getNewVelocity() {
		return Read<Vector3>(this->playerModel + 0x21C); //private Vector3 newVelocity;
	}

	Vector3 getPosition() {
		return Read<Vector3>(this->visualState + 0x90);//0x90
	}

	Vector3 getRecoilAngles() {
		return ReadChain<Vector3>(this->player, { (uint64_t)0x4E0, (uint64_t)0x64 });
	}

	Vector3 getViewAngles() {
		return ReadChain<Vector3>(this->player, { (uint64_t)0x4E0, (uint64_t)0x3C });// public PlayerInput input;
	}

	std::string getName() {
		return this->getASCIIName(this->getPlayerName());
	}



	//Testing 
	void TestNight(float time)
	{
		DWORD64 ObjManager = Read<DWORD64>(uBase + 0x17C1F18); if (!ObjManager) return;
		DWORD64 Obj = Read<DWORD64>(ObjManager + 0x8); (Obj && (Obj) != Read<DWORD64>(ObjManager)); Obj = Read<DWORD64>(Obj + 0x8);
		DWORD64 GameObject = Read<DWORD64>(Obj + 0x10);
		DWORD64 ObjClass = Read<DWORD64>(GameObject + 0x30);
		DWORD64 Entity1 = Read<DWORD64>(ObjClass + 0x18);
		DWORD64 Dome = Read<DWORD64>(Entity1 + 0x28);
		DWORD64 TodCycle = Read<DWORD64>(Dome + 0x38);
		Write<float>(TodCycle + 0x10, time);
	}

	void LongNeck()
	{
		if (GetAsyncKeyState(Settings::LongNeckKey))
		{
			DWORD64 eyes = Read<DWORD64>(this->player + 0x658);
			Write<Vector3>(eyes + 0x38, Vector3(0, (0.8f), 0));
		}
	}


	HeldItem getHeldItem()
	{
		int active_weapon_id = Read<int>(this->player + 0x5C8); //private uint clActiveItem;

		uint64_t items = ReadChain<uint64_t>(this->player, { (uint64_t)0x660, (uint64_t)0x28, (uint64_t)0x38, 0x10 }); //public PlayerInventory inventory;


		//std::cout << active_weapon_id << std::endl;

		//std::cout << "Held weapon: found :" <<  items << std::endl;


		for (int items_on_belt = 0; items_on_belt <= 6; items_on_belt++)
		{
			uint64_t item = Read<uint64_t>(items + 0x20 + (items_on_belt * 0x8));

			int active_weapon = Read<uint32_t>(item + 0x28);

			if (active_weapon_id == active_weapon)
			{
				HeldItem item_obj = HeldItem(item);

				return item_obj;
			}
		}

		return 0;
	}

	std::wstring getPlayerName() {
		std::wstring name = ReadUnicode(Read<uint64_t>(this->player + 0x6B0) + 0x14); //BasePlayer -> protected string _displayName

		if (name.find(safe_strW(L"Scientist")) == 0)
			return safe_strW(L"Scientist");

		return name;
	}

public:

	uintptr_t player{};
	uintptr_t visualState{};
	std::string name{};
	bool isCalled{};
	std::wstring nameW{};
	Vector3 position{};
	uint32_t playerFlags{};
	uint64_t playerModel{};
	uint64_t modelState{};
	float health{};

}; std::unique_ptr<std::vector<BasePlayer>> entityList;

#pragma endregion

class PlayerCorpse {
public:

	PlayerCorpse() {}

	PlayerCorpse(uintptr_t _ent, uintptr_t _trans, uintptr_t _obj) {
		this->ent = Read<uintptr_t>(_ent + 0x28);
		this->trans = Read<uintptr_t>(_trans + 0x38);

		this->name = ReadNative(_obj + 0x60);
	}

public:

	uintptr_t ent{};
	uintptr_t trans{};
	std::string name{};
}; std::unique_ptr<std::vector<PlayerCorpse>> corpseList;

#pragma region PMClass

class PlayerMovement : public BasePlayer, PlayerCorpse {
public:

	PlayerMovement() {}

	PlayerMovement(uintptr_t player) {        //0x4D0
		this->playerMovement = Read<uintptr_t>(player + 0x4E8); //public BaseMovement movement;
	}

	void alwaysShoot() {
		Write<float>(this->playerMovement + 0x48, 1);
	}

	void speedHack(int speed) {
		Write<float>(this->player + 0x714, speed);
	}


	void setFov() {
		auto klass = Read<DWORD64>(gBase + ConVar_Graphics_c); //ConVar.Graphics_TypeInfo
		auto staticFields = Read<DWORD64>(klass + 0xB8);
		Write<float>(staticFields + 0x18, Settings::FovSlider);//0x18 => m_camera
	}



	void infiniteJump() {
		if (GetAsyncKeyState(Settings::jumpKey))
		{
			Write<float>(this->playerMovement + 0xC0, 0);
			Write<float>(this->playerMovement + 0xC4, 0);
			Write<float>(this->playerMovement + 0xBC, 100000);
		}
	}


	void spiderClimb() {
		Write<float>(this->playerMovement + 0xBC, 0.f);
		Write<float>(this->playerMovement + 0xC0, 0.f);
	}

	void walkOnWater() {
		if (GetAsyncKeyState(Settings::walkWaterKEY)) {
			Write<float>(this->playerMovement + 0xB4, 0.f);//groundAngle
			Write<float>(this->playerMovement + 0xB8, 0.f);//groundAngleNew
			Write<float>(this->playerMovement + 0x74, 0.f);//gravityMultiplier
		}
		else {
			Write<float>(this->playerMovement + 0x74, 2.5f);//gravityMultiplier
		}
	}

public:

	uint64_t playerMovement{};
};

#pragma endregion

class BaseResource {
public:
	BaseResource() {}

	BaseResource(uintptr_t _ent, uintptr_t _trans, uintptr_t _obj) {
		this->ent = Read<uintptr_t>(_ent + 0x28);
		this->trans = Read<uintptr_t>(_trans + 0x38);

		this->name = ReadNative(_obj + 0x60);

		if (this->name.find(safe_str("stone-ore")) != std::string::npos)
			this->name = safe_str("stone ore");
		else if (this->name.find(safe_str("sulfur-ore")) != std::string::npos)
			this->name = safe_str("sulfur ore");
		else if (this->name.find(safe_str("metal-ore")) != std::string::npos)
			this->name = safe_str("metal ore");
		else if (this->name.find(safe_str("hemp-collectable")) != std::string::npos)
			this->name = safe_str("cloth");
		else if (this->name.find(safe_str("metal-collectable")) != std::string::npos)
			this->name = safe_str("metal");
		else if (this->name.find(safe_str("stone-collectable")) != std::string::npos)
			this->name = safe_str("stone");
		else if (this->name.find(safe_str("sulfur-collectable")) != std::string::npos)
			this->name = safe_str("sulfur");
		else if (this->name.find(safe_str("wood-collectable")) != std::string::npos)
			this->name = safe_str("wood");
		else if (this->name.find(safe_str("small_stash.item")) != std::string::npos)
			this->name = safe_str("Stash");
		else
			this->name = safe_str("resource");

	}

public:
	uintptr_t ent{};
	uintptr_t trans{};
	std::string name{};
}; std::unique_ptr<std::vector<BaseResource>> oreList;//scans for ores

#pragma region LPClass

class LocalPlayer {
public:
	std::unique_ptr<BasePlayer> Player;
	std::unique_ptr<PlayerMovement> Movement;
}; std::unique_ptr<LocalPlayer> localPlayer;

#pragma endregion