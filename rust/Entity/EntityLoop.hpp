#pragma once

#pragma region Includes
#include "../SDK/Classes.hpp"
#include "../SDK/BasePlayer.hpp"
#include "../SDK/Imports.hpp"
#include "../SDK/Driver.hpp"
#pragma endregion

namespace Entity {
#pragma region PlayerChain

	void EntityLoop() {
		auto BaseNetworkable = IL2CPPScan(safe_str("BaseNetworkable"));

		/*{ 0xb8, 0x0, 0x10, 0x28 }*/

		while (true)
		{
			std::unique_ptr<std::vector<BaseEntity>> t_entList = std::make_unique<std::vector<BaseEntity>>();
			std::unique_ptr<std::vector<EntityCorpse>> t_corpseList = std::make_unique<std::vector<EntityCorpse>>();
			std::unique_ptr<std::vector<BaseMiscEntity>> t_oreList = std::make_unique<std::vector<BaseMiscEntity>>();

			auto unk1 = Read<uintptr_t>(BaseNetworkable + 0xB8);
			auto clientEntities = Read<uintptr_t>(unk1);
			auto entityRealm = Read<uintptr_t>(clientEntities + 0x10);
			auto bufferList = Read<uintptr_t>(entityRealm + 0x28);
			auto objectList = Read<uintptr_t>(bufferList + 0x18);
			auto objectListSize = Read<uint32_t>(bufferList + 0x10);

			for (auto i = 0; i < objectListSize; i++) {
				auto curObject = Read<uintptr_t>(objectList + (0x20 + (i * 8)));
				auto baseObject = Read<uintptr_t>(curObject + 0x10);
				auto object = Read<uintptr_t>(baseObject + 0x30);
				auto tag = Read<WORD>(object + 0x54);
				auto prefebName = ReadNative(object + 0x60);

				if (tag == player) { //6
					auto objectClass = Read<uintptr_t>(object + 0x30);
					auto entity = Read<uintptr_t>(objectClass + 0x18);
					auto transform = Read<uintptr_t>(objectClass + 0x8);

					std::unique_ptr<BaseEntity> BPlayer = std::make_unique<BaseEntity>(entity, transform, object);

					if (BPlayer->isLocalPlayer()) {
						localPlayer->Player = std::make_unique<BaseEntity>(entity, transform, object);
						localPlayer->Movement = std::make_unique<EntityMovment>(localPlayer->Player->player);
					}

					if (!BPlayer->isDead()) t_entList->push_back(*BPlayer); continue;
				}

				
				if (prefebName.find(safe_str("assets/prefabs/misc/item drop/item_drop_backpack.prefab")) != std::string::npos || prefebName.find(safe_str("assets/prefabs/player/player_corpse.prefab")) != std::string::npos) {
					auto objectClass = Read<uintptr_t>(object + 0x30);
					auto entity = Read<uintptr_t>(objectClass + 0x18);
					auto transform = Read<uintptr_t>(objectClass + 0x8);

					std::unique_ptr<EntityCorpse> CEntity = std::make_unique<EntityCorpse>(entity, transform, object);
					t_corpseList->push_back(*CEntity); continue;
				}

				if (prefebName.find(safe_str("autospawn/resource/ores")) != std::string::npos || prefebName.find(safe_str("autospawn/collectable/")) != std::string::npos || prefebName.find(safe_str("deployable/small stash/")) != std::string::npos) {
					if (prefebName.find(safe_str("stone-ore")) != std::string::npos) {
						if (Settings::selectedOres[0] == false) continue;
					}
					else if (prefebName.find(safe_str("sulfur-ore")) != std::string::npos) {
						if (Settings::selectedOres[1] == false) continue;
					}
					else if (prefebName.find(safe_str("metal-ore")) != std::string::npos) {
						if (Settings::selectedOres[2] == false) continue;
					}
					else if (prefebName.find(safe_str("hemp-collectable")) != std::string::npos) {
						if (Settings::selectedOres[3] == false) continue;
					}
					else if (prefebName.find(safe_str("metal-collectable")) != std::string::npos) {
						if (Settings::selectedOres[4] == false) continue;
					}
					else if (prefebName.find(safe_str("stone-collectable")) != std::string::npos) {
						if (Settings::selectedOres[5] == false) continue;
					}
					else if (prefebName.find(safe_str("sulfur-collectable")) != std::string::npos) {
						if (Settings::selectedOres[6] == false) continue;
					}
					else if (prefebName.find(safe_str("wood-collectable")) != std::string::npos) {
						if (Settings::selectedOres[7] == false) continue;
					}
					else if (prefebName.find(safe_str("small_stash_deployed")) != std::string::npos) {
						if (Settings::selectedOres[8] == false) 
							continue;
						else
						{
							uintptr_t stashstatus = Read<uintptr_t>(curObject + 0x130);

							if (stashstatus != 2048)
								continue;
							//std::cout << std::hex << curObject << std::endl;
						}
					}
					
					else continue;

					auto objectClass = Read<uintptr_t>(object + 0x30);
					auto entity = Read<uintptr_t>(objectClass + 0x18);
					auto transform = Read<uintptr_t>(objectClass + 0x8);

					std::unique_ptr<BaseMiscEntity> oreEntity = std::make_unique<BaseMiscEntity>(entity, transform, object);

					t_oreList->push_back(*oreEntity); continue;
				}
			}

			entityList->clear();
			corpseList->clear();
			oreList->clear();

			Mutex->PlayerSync->lock();
			*entityList = *t_entList;
			*corpseList = *t_corpseList;
			*oreList = *t_oreList;
			Mutex->PlayerSync->unlock();
		}
	}
}
#pragma endregion