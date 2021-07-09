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

						//localPlayer->Player->getHeldItem().setNoAimCone();
						//localPlayer->Player->getHeldItem().setNoSway();

						if (AimFov(curEntity) < Settings::aimbotFov) {
							AimbotTarget(curEntity);
						}
					}
				}
			}
			else SleepEx(550, false); //550
		}
	}
}