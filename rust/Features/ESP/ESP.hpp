#pragma once
#include "../../SDK/Classes.hpp"
#include "../../Overlay/Overlay.hpp"
#include "../../Overlay/Menu/Settings.hpp"
#include "../../SDK/BasePlayer.hpp"
#include "../Aimbot/DoAimbot.hpp"
#include "DrawESP.hpp"
#include <array>
#include <future>

using namespace std::string_literals;

namespace ESP {
	void __fastcall Run() {

		uintptr_t gomPtr = Read<uintptr_t>(uBase + 0x17C1F18); //game object manager | Chain + 0x17C1F18 -> 0x8 -> 0x10 -> 0x30 -> 0x18 -> 0x2E4
		uintptr_t taggedObjects = Read<uintptr_t>(gomPtr + 0x8);
		uintptr_t gameObject = Read<uintptr_t>(taggedObjects + 0x10);
		uintptr_t objectClass = Read<uintptr_t>(gameObject + 0x30);
		uintptr_t entity = Read<uintptr_t>(objectClass + 0x18);

		pViewMatrix = Read<Matrix4x4>(entity + 0x2E4); //camera


		uintptr_t m_skyDome = NULL;
		uintptr_t m_camer = NULL;
		uintptr_t last_object = NULL;
		auto current_tagged_base = Read<uintptr_t>(gBase + 0x08);
		auto current_tagged_obj = Read<uintptr_t>(current_tagged_base + 0x10);


		if (Settings::drawCrosshair)
			DrawCrosshair();

		if (Settings::niggerCross)
			Nigger();



		if (Settings::enableAimbot)
			Render::Circle(ImVec2(screenWidth / 2, screenHeight / 2), Settings::aimbotFov, ImColor(255, 255, 255));

		std::unique_ptr<std::vector<BasePlayer>> local_players = std::make_unique<std::vector<BasePlayer>>();
		std::unique_ptr<std::vector<PlayerCorpse>> local_corpse = std::make_unique<std::vector<PlayerCorpse>>();
		std::unique_ptr<std::vector<BaseResource>> local_ore = std::make_unique<std::vector<BaseResource>>();

		Mutex->PlayerSync->lock();
		*local_players = *entityList;
		*local_corpse = *corpseList;
		*local_ore = *oreList;
		Mutex->PlayerSync->unlock();

		for (unsigned long i = 0; i < local_ore->size(); ++i) {
			std::unique_ptr<BaseResource> curOre = std::make_unique<BaseResource>(local_ore->at(i));
			auto position = Read<Vector3>(curOre->trans + 0x90);//world position = 0x90
			auto distance = (int)Math::Distance(&localPlayer->Player->position, &position);
			if (distance < 200)
			{
				Vector2 pos;

				std::string nameStr = curOre->name;
				std::string distanceStr = std::to_string(distance) + "M";

				if (!Utils::WorldToScreen(position, pos)) continue;
				auto text_size = ImGui::CalcTextSize(nameStr.c_str());
				auto text_sizeDistance = ImGui::CalcTextSize(distanceStr.c_str());
				//auto text_sizeDistance = ImGui::CalcTextSize(distanceStr.c_str());

				Render::DrawCornerBox(ImVec2(pos.x - 7, pos.y - 10), ImVec2(10, 10), ImColor(255, 255, 255));

				Render::Text(ImVec2(pos.x - text_size.x / 2, pos.y + 12 - text_size.y), nameStr, ImColor(255, 255, 255), true, Overlay::playerName, Overlay::playerName->FontSize);
				Render::Text(ImVec2(pos.x - text_sizeDistance.x / 2, pos.y + 21 - text_sizeDistance.y), distanceStr, ImColor(255, 255, 255), true, Overlay::playerName, Overlay::playerName->FontSize);
			}
		}


		for (unsigned long i = 0; i < local_corpse->size(); ++i) {
			std::unique_ptr<PlayerCorpse> curCorpse = std::make_unique<PlayerCorpse>(local_corpse->at(i));

			auto position = Read<Vector3>(curCorpse->trans + 0x90);//world position
			auto distance = (int)Math::Distance(&localPlayer->Player->position, &position);
			Vector2 pos;

			if (curCorpse->name.find("player/player_corpse") != std::string::npos) {

				std::string nameStr = "Dead Body";
				std::string distanceStr = std::to_string(distance) + "M";

				if (!Utils::WorldToScreen(position, pos)) continue;

				auto text_size = ImGui::CalcTextSize(nameStr.c_str());
				//auto text_sizeDistance = ImGui::CalcTextSize(distanceStr.c_str());

				Render::DrawCornerBox(ImVec2(pos.x - 7, pos.y - 10), ImVec2(10, 10), ImColor(255, 255, 255));

				Render::Text(ImVec2(pos.x - text_size.x / 2, pos.y + 12 - text_size.y), nameStr, ImColor(255, 255, 255), true, Overlay::playerName, Overlay::playerName->FontSize);
				//Render::Text(ImVec2(pos.x - text_sizeDistance.x / 2, pos.y + 21 - text_sizeDistance.y), distanceStr, ImColor(255, 255, 255), true, Overlay::playerName, Overlay::playerName->FontSize);
			}
		}

		for (unsigned long i = 0; i < local_players->size(); ++i)
		{
			std::unique_ptr<BasePlayer> curEntity = std::make_unique<BasePlayer>(local_players->at(i));

			//Vector3 entityPosition = curEntity->getPosition();

			auto distance = (int)Math::Distance(&localPlayer->Player->position, &curEntity->position);

			if (curEntity->isLocalPlayer()) continue;

			if (!curEntity->IsInView()) continue;

			if (Settings::drawSkeleton && distance < Settings::skeletonDistance)
				DrawSkeleton(curEntity->player);

			if (Settings::drawBox && distance < Settings::boxDistance)
				DrawBox(curEntity->player, curEntity->isSameTeam(localPlayer->Player));

			if (Settings::drawName && distance < Settings::nameDistance)
				DrawPlayerName(curEntity->player, curEntity->getName(), distance);

			if (Settings::drawHealthBar && distance < Settings::healthDistance)
				DrawPlayerHealth(curEntity->player, curEntity->health);
		}
	}
}