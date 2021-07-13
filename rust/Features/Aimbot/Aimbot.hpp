#pragma once
#include "../../SDK/Classes.hpp"
#include "../../Overlay/Menu/Settings.hpp"
#include "../../SDK/BasePlayer.hpp"

namespace Aimbot {
	std::map<std::string, float> BulletSpeeds = {
		{ std::string("ammo.rifle"), 1.0f },
		{ std::string("ammo.rifle.hv"), 1.2f },
		{ std::string("ammo.rifle.explosive"), 0.6f },
		{ std::string("ammo.rifle.incendiary"), 0.6f },

		{ std::string("ammo.pistol"), 1.0f },
		{ std::string("ammo.pistol.hv"), 1.33333f },
		{ std::string("ammo.pistol.incendiary"), 0.75f },

		{ std::string("arrow.wooden"), 1.0f },
		{ std::string("arrow.hv"), 1.6f },
		{ std::string("arrow.fire"), 0.8f },
		{ std::string("arrow.bone"), 0.9f },

		{ std::string("ammo.handmade.shell"), 1.0f },
		{ std::string("ammo.shotgun.slug"), 2.25f },
		{ std::string("ammo.shotgun.fire"), 1.0f },
		{ std::string("ammo.shotgun"), 2.25f },

		{ std::string("ammo.nailgun.nails"), 1.0f }
	};

	std::map<std::string, float> BulletGravity = {
		{ std::string("ammo.rifle"), 1.0f },
		{ std::string("ammo.rifle.hv"), 1.0f },
		{ std::string("ammo.rifle.explosive"), 1.25f },
		{ std::string("ammo.rifle.incendiary"), 1.0f },

		{ std::string("ammo.pistol"), 1.0f },
		{ std::string("ammo.pistol.hv"), 1.0f },
		{ std::string("ammo.pistol.incendiary"), 1.0f },

		{ std::string("arrow.wooden"), 0.75f },
		{ std::string("arrow.hv"), 0.5f },
		{ std::string("arrow.fire"), 1.0f },
		{ std::string("arrow.bone"), 0.75f },

		{ std::string("ammo.handmade.shell"), 1.0f },
		{ std::string("ammo.shotgun.slug"), 1.0f },
		{ std::string("ammo.shotgun.fire"), 1.0f },
		{ std::string("ammo.shotgun"), 1.0f },

		{ std::string("ammo.nailgun.nails"), 0.75f }
	};

	float distance_cursor(Vector2 vec)
	{
		POINT p;
		if (GetCursorPos(&p))
		{
			float ydist = (vec.y - p.y);
			float xdist = (vec.x - p.x);
			float ret = sqrt(pow(ydist, 2) + pow(xdist, 2));
			return ret;
		}
	}

	float ProjectileSpeed_Normal() {
		std::string held_item = localPlayer->Player->getHeldItem().GetItemName();
		float Ammunition_Multiplier = BulletSpeeds[localPlayer->Player->getHeldItem().GetAmmoType()];

		if (held_item == "No Item")                 return 300.0f;

		if (held_item == "rifle.ak")                return 375.0f * Ammunition_Multiplier;
		if (held_item == "rifle.lr300")             return 375.0f * Ammunition_Multiplier;
		if (held_item == "rifle.bolt")              return 656.0f * Ammunition_Multiplier;
		if (held_item == "rifle.l96")               return 1125.0f * Ammunition_Multiplier;
		if (held_item == "rifle.m39")               return 469.0f * Ammunition_Multiplier;
		if (held_item == "rifle.semiauto")          return 375.0f * Ammunition_Multiplier;

		if (held_item == "lmg.m249")                return 488.0f * Ammunition_Multiplier;

		if (held_item == "smg.thompson")            return 300.0f * Ammunition_Multiplier;
		if (held_item == "smg.custom")              return 240.0f * Ammunition_Multiplier;
		if (held_item == "smg.mp5")                 return 240.0f * Ammunition_Multiplier;

		if (held_item == "pistol.python")           return 300.0f * Ammunition_Multiplier;
		if (held_item == "pistol.semi")             return 300.0f * Ammunition_Multiplier;
		if (held_item == "pistol.revolver")         return 300.0f * Ammunition_Multiplier;
		if (held_item == "pistol.m92")              return 300.0f * Ammunition_Multiplier;
		if (held_item == "pistol.eoka")             return 100.0f * Ammunition_Multiplier;
		if (held_item == "pistol.nailgun")          return 50.0f;

		if (held_item == "crossbow")               return 75.0f * Ammunition_Multiplier;
		if (held_item == "bow.compound")            return 100.0f * Ammunition_Multiplier;
		if (held_item == "bow.hunting")             return 50.0f * Ammunition_Multiplier;

		if (held_item == "shotgun.pump")            return 100.0f * Ammunition_Multiplier;
		if (held_item == "shotgun.spas12")          return 100.0f * Ammunition_Multiplier;
		if (held_item == "shotgun.waterpipe")       return 100.0f * Ammunition_Multiplier;
		if (held_item == "shotgun.doublebarrel")    return 100.0f * Ammunition_Multiplier;

		return 300.0f;
	}

	float AimFov(std::unique_ptr<BaseEntity>& BPlayer, BonesList bone)
	{
		Vector2 ScreenPos;
		if (!Utils::WorldToScreen(Utils::GetBonePosition(BPlayer->player, bone), ScreenPos)) return 1000.f;
		return Math::Calc2D_Dist(Vector2(screenWidth / 2, screenHeight / 2), ScreenPos);
	}

	

	Vector3 Prediction(const Vector3& LP_Pos, std::unique_ptr<BaseEntity>& Player, BonesList Bone) {
		Vector3 BonePos = Utils::GetBonePosition(Player->player, Bone);
		float Dist = Math::Calc3D_Dist(LP_Pos, BonePos);

		if (Dist > 0.001f) {
			float BulletTime = Dist / ProjectileSpeed_Normal();
			Vector3 vel = Player->getNewVelocity() * 0.75f;
			Vector3 PredictVel = vel * BulletTime;
			BonePos += PredictVel; BonePos.y += (4.905f * BulletTime * BulletTime);
		} return BonePos;
	}

	void Normalize(float& Yaw, float& Pitch) {
		if (Pitch < -89) Pitch = -89;
		else if (Pitch > 89) Pitch = 89;
		if (Yaw < -360) Yaw += 360;
		else if (Yaw > 360) Yaw -= 360;
	}

	void SmoothAim(Vector2& Angle, float smooth) {
		Angle.x /= smooth;
		Angle.y /= smooth;
	}

	Vector4 calculate_quaternion(Vector3 euler)
	{
		Vector4 result{};

		const auto yaw = (euler.z * 0.01745329251f) * 0.5f;
		const auto sy = std::sin(yaw);
		const auto cy = std::cos(yaw);

		const auto roll = (euler.x * 0.01745329251f) * 0.5f;
		const auto sr = std::sin(roll);
		const auto cr = std::cos(roll);

		constexpr auto sp = 0.f;
		constexpr auto cp = 1.f;

		result.x = cy * sr * cp - sy * cr * sp;
		result.y = cy * cr * sp + sy * sr * cp;
		result.z = sy * cr * cp - cy * sr * sp;
		result.w = cy * cr * cp + sy * sr * sp;

		return result;
	}


	Vector3 calculate_angle(const Vector3& source, const Vector3& destination)
	{
		constexpr auto r2d = 57.2957795131f; /* 180 / pi, used for conversion from radians to degrees */
		constexpr auto d2r = 0.01745329251f; /* pi / 180, used for conversion from degrees to radians */

		Vector3 direction = source - destination;
		return { std::asin(direction.y / direction.Length()) * r2d, -std::atan2(direction.x, -direction.z) * r2d, 0.f };
	}

	void NewAim(std::unique_ptr<BaseEntity>& BPlayer, BonesList Bone)
	{
		Vector3 localpos = Utils::GetBonePosition(localPlayer->Player->player, BonesList::neck);
		//Vector3 posTargetPlayer = localPlayer->Player->getPosition();
		Vector3 PlayerPos = Prediction(localpos, BPlayer, Bone);
		Vector2 AngleToAim = Math::CalcAngle(localpos, PlayerPos);
		bool flag = localpos != Vector3(0, 0, 0);
		if (flag)
		{
			float number1 = AngleToAim.x;
			float number2 = AngleToAim.y;
			while (number1 >= 180.0f)
			{
				number1 -= 360.0f;
			}
			while (number1 <= -180.0f)
			{
				number1 += 360.0f;
			}
			if (number1 > 89.0f)
			{
				number1 = 89.0f;
			}
			else if (number1 < -89.0f)
			{
				number1 = -89.0f;
			}
			while (number2 >= 360.0f)
			{
				number2 -= 360.0f;
			}
			while (number2 <= -360.0f)
			{
				number2 += 75.0f;
			}
			uint64_t playerInput = Read<uint64_t>(localPlayer->Player->player + 0x4E0);
			if (!playerInput);
			Vector3 bodyAngles = Vector3(number1, number2, 0.0f);
			Vector4 bodyRoations = calculate_quaternion(bodyAngles);

			//Write<Vector3>(playerInput + 0x3C, calculate_angle(localpos, bodyAngles));
			localPlayer->Player->setViewAngles(AngleToAim);
		}
	}


	void AimbotTarget(std::unique_ptr<BaseEntity>& BPlayer, BonesList Bone) {
		Vector3 Local = Utils::GetBonePosition(localPlayer->Player->player, BonesList::neck);
		Vector3 PlayerPos = Prediction(Local, BPlayer, Bone);



			Vector2 recoil_angles = Vector2{ localPlayer->Player->getRecoilAngles().x, localPlayer->Player->getRecoilAngles().y };

			Vector2 AngleToAim = Math::CalcAngle(Local, PlayerPos);
			Normalize(AngleToAim.y, AngleToAim.x);
			if (isnan(AngleToAim.x) || isnan(AngleToAim.y))
				return;

			if (Settings::enableSmoothing) {
				AngleToAim -= Vector2{ localPlayer->Player->getViewAngles().x, localPlayer->Player->getViewAngles().y };
				SmoothAim(AngleToAim, Settings::aimbotSmoothing);
				AngleToAim += Vector2{ localPlayer->Player->getViewAngles().x, localPlayer->Player->getViewAngles().y };
			}

			if (Settings::enableCompensateRecoil) {
				AngleToAim -= recoil_angles;
			}

			localPlayer->Player->setViewAngles(AngleToAim);
	}
}
