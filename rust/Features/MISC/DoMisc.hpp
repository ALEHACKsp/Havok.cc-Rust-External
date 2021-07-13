#pragma once
#include "Misc.hpp"
#include "../../SDK/BasePlayer.hpp"

namespace Misc {
	void DoMisc() {
		while (true) {
				std::unique_ptr<std::vector<BaseEntity>> local_players = std::make_unique<std::vector<BaseEntity>>();
				std::unique_ptr<HeldItem> heldItem = std::make_unique<HeldItem>();

				Mutex->PlayerSync->lock();
				*local_players = *entityList;
				Mutex->PlayerSync->unlock();

			for (unsigned long i = 0; i < local_players->size(); ++i)	{
				*heldItem = localPlayer->Player->getHeldItem();

				if (Settings::speedhack && GetAsyncKeyState(Settings::speedHackkey))
				{
					localPlayer->Movement->speedHack(-1); // fast
				}
				else if (!GetAsyncKeyState(Settings::speedHackkey))
				{
					localPlayer->Movement->speedHack(0);
				}

				if (Settings::shootInAir)
				{
					localPlayer->Player->LongNeck();  localPlayer->Player->setModelFlag(MStateFlags::OnGround); localPlayer->Movement->alwaysShoot();
				}

				if (Settings::thirdperson) localPlayer->Player->setPlayerFlag(BPlayerFlags::ThirdPersonViewmode);
				if (Settings::adminFlag) localPlayer->Player->setPlayerFlag(BPlayerFlags::IsAdmin);
				if (Settings::debugFlag) localPlayer->Player->setModelFlag(MStateFlags::Sleeping);

					
				if (Settings::freeze) localPlayer->Player->isFrozen();


				if (Settings::SuperJump) localPlayer->Movement->Gravity();
				if (Settings::infinateJump) localPlayer->Movement->infiniteJump();
				if (Settings::walkOnWater) localPlayer->Movement->walkOnWater();
				if (Settings::spiderClimb) localPlayer->Movement->spiderClimb();
				if (Settings::DebugFix) localPlayer->Movement->FixDebug();
				
				
				localPlayer->Movement->FlyHack();


				//Sky Shit
				if (Settings::night_mode) localPlayer->Player->TestNight(Settings::time);
				if (Settings::skyColorBool) localPlayer->Player->TestColor(Settings::SkyColor);
				if (Settings::nightSky) localPlayer->Player->NightMode();

				if (Settings::FovSlider > 75) localPlayer->Movement->setFov();
				if (Settings::zoom) localPlayer->Movement->zoom();
				if (Settings::waterLevel) localPlayer->Player->SetWater();
				

				if (heldItem->IsWeapon())
				{
					if (Settings::noRecoil) heldItem->noRecoil(); 
					if (Settings::noSpread) heldItem->AntiSpread();
					if (Settings::rapidFire) heldItem->rapidFire();
					if (Settings::instantCompound) heldItem->instantCompound();
					if (Settings::fastSwitchWeapons) heldItem->fastSwitch();
					if (Settings::tapeoka) heldItem->instantEoka();
					if (Settings::longhit) heldItem->setLonghit(5.f);
					if (Settings::runhit) heldItem->RunHit();

					heldItem->setNoAimCone();
				}
			}
		}
	}
}
