#pragma once
#include "Aimbot.hpp"
BonesList bone;
namespace Aimbot {
	std::unique_ptr<BaseEntity> getTarget()
	{
		std::unique_ptr<std::vector<BaseEntity>> local_players = std::make_unique<std::vector<BaseEntity>>();

		Mutex->PlayerSync->lock();
		*local_players = *entityList;
		Mutex->PlayerSync->unlock();

		for (unsigned long i = 0; i < local_players->size(); ++i) {
			std::unique_ptr<BaseEntity> curEntity = std::make_unique<BaseEntity>(local_players->at(i));

			if (curEntity->isLocalPlayer()) continue;

			if (curEntity->isSameTeam(localPlayer->Player)) continue;

			if (!curEntity->IsInView()) continue;

			if (curEntity->health < 0.00f) continue;

			switch (Settings::aimbotHitbox)
			{
			case 0: bone = BonesList::neck; break;
			case 1: bone = BonesList::spine1; break;
			case 2: bone = BonesList::pelvis; break;
			}
			if (bone)
			{
				if (AimFov(curEntity, bone) < Settings::aimbotFov)
					return curEntity;
			}
			
			

			//if (AimFov(curEntity, bone) < Settings::aimbotFov) {
			//	AimbotTarget(curEntity, bone);
			//}
		}
	}

	void DoAimbot() {
		while (true) {
			if (Settings::enableAimbot) {
				auto target = getTarget();
				
				if (GetAsyncKeyState(Settings::aimbotKey) && target) {
					auto distance = (int)Math::Distance(&localPlayer->Player->position, &target->position);
					if(target->player && distance <= Settings::aimbotDistance)
						AimbotTarget(target, bone);
				}
			}
			else SleepEx(20, false); //550
		}
	}
}