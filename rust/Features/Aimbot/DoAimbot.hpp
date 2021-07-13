#pragma once
#include "Aimbot.hpp"

static bool isEnabled;

namespace Aimbot {
	void DoAimbot() {
		while (true) {
			if (Settings::enableAimbot) {
				if (GetAsyncKeyState(Settings::aimbotKey)) {
					std::unique_ptr<std::vector<BasePlayer>> local_players = std::make_unique<std::vector<BasePlayer>>();

					Mutex->PlayerSync->lock();
					*local_players = *entityList;
					Mutex->PlayerSync->unlock();

					for (unsigned long i = 0; i < local_players->size(); ++i) {
						std::unique_ptr<BasePlayer> curEntity = std::make_unique<BasePlayer>(local_players->at(i));

						if (curEntity->isLocalPlayer()) continue;

						if (curEntity->isSameTeam(localPlayer->Player)) continue;

						if (!curEntity->IsInView()) continue;

						if (curEntity->health < 0.00f) continue;

						BonesList bone;
						switch (Settings::aimbotHitbox)
						{
						case 0: bone = BonesList::neck; break;
						case 1: bone = BonesList::spine1; break;
						case 2: bone = BonesList::pelvis; break;
						}

						if (AimFov(curEntity, bone) < Settings::aimbotFov) {
							AimbotTarget(curEntity, bone);
							//NewAim(curEntity, bone);
						}
					}
				}
			}
			else SleepEx(20, false); //550
		}
	}
}