#pragma once
#include "Misc.hpp"
#include "../../SDK/BasePlayer.hpp"

namespace Misc {
	void DoMisc() {
		while (true) {
				std::unique_ptr<std::vector<BasePlayer>> local_players = std::make_unique<std::vector<BasePlayer>>();
				std::unique_ptr<HeldItem> heldItem = std::make_unique<HeldItem>();

				Mutex->PlayerSync->lock();
				*local_players = *entityList;
				Mutex->PlayerSync->unlock();

			for (unsigned long i = 0; i < local_players->size(); ++i)	{
				*heldItem = localPlayer->Player->getHeldItem();

				if (Settings::shootInAir)
				{
					localPlayer->Player->setModelFlag(MStateFlags::OnGround);
					localPlayer->Movement->alwaysShoot();
				}

				if (Settings::thirdperson) localPlayer->Player->setPlayerFlag(BPlayerFlags::ThirdPersonViewmode);
				if (Settings::adminFlag) localPlayer->Player->setPlayerFlag(BPlayerFlags::IsAdmin);
				//if (Settings::noRecoil) heldItem->noRecoil();

				//localPlayer->Player->blockSprint();

					
				//if (Settings::adminFlag) localPlayer->Player->setAdmin();

				if (Settings::infinateJump) localPlayer->Movement->infiniteJump();
				if (Settings::walkOnWater) localPlayer->Movement->walkOnWater();
				if (Settings::spiderClimb) localPlayer->Movement->spiderClimb();


				if (Settings::FovSlider > 90) localPlayer->Movement->setFov(); 

				if (heldItem->IsWeapon())
				{
					if (Settings::noRecoil) heldItem->noRecoil();
					if (Settings::rapidFire) heldItem->rapidFire();
					if (Settings::instantCompound) heldItem->instantCompound();
					if (Settings::fastSwitchWeapons) heldItem->fastSwitch();
					if (Settings::tapeoka) heldItem->instantEoka();

					heldItem->setNoAimCone();
				}
			}
		}
	}
}