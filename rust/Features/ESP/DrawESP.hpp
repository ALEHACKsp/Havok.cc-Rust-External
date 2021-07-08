#pragma once
#include "ESP.hpp"

namespace ESP {
	void __fastcall DrawSkeleton(uint64_t player) {
		std::array<BonesList, 15> Bones = {
			r_foot, l_knee, l_hip,
			l_foot, r_knee, r_hip,
			spine1, neck, head,
			l_upperarm, l_forearm, l_hand,
			r_upperarm, r_forearm, r_hand
		}; std::array<Vector2, Bones.size()> BonesPos;

		for (int i = 0; i < BonesPos.size(); ++i) {
			if (!(Utils::WorldToScreen(Utils::GetBonePosition(player, Bones[i]), BonesPos.at(i)))) continue;
		}

		for (int j = 0; j < BonesPos.size(); j += 3) {
			Render::Line({ BonesPos[j].x, BonesPos[j].y }, { BonesPos[j + 1].x, BonesPos[j + 1].y }, Render::FtIM(Settings::drawColor_skeleton), 1.0f);
			Render::Line({ BonesPos[j + 1].x, BonesPos[j + 1].y }, { BonesPos[j + 2].x, BonesPos[j + 2].y }, Render::FtIM(Settings::drawColor_skeleton), 1.0f);
		}

		Render::Line({ BonesPos[2].x, BonesPos[2].y }, { BonesPos[6].x, BonesPos[6].y }, Render::FtIM(Settings::drawColor_skeleton), 1.0f);
		Render::Line({ BonesPos[5].x, BonesPos[5].y }, { BonesPos[6].x, BonesPos[6].y }, Render::FtIM(Settings::drawColor_skeleton), 1.0f);
		Render::Line({ BonesPos[9].x, BonesPos[9].y }, { BonesPos[7].x, BonesPos[7].y }, Render::FtIM(Settings::drawColor_skeleton), 1.0f);
		Render::Line({ BonesPos[12].x, BonesPos[12].y }, { BonesPos[7].x, BonesPos[7].y }, Render::FtIM(Settings::drawColor_skeleton), 1.0f);
	}

	void __fastcall DrawBox(uint64_t player, bool isSameTeam) {
		Vector3 head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.2, 0));
		Vector3 feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
		Vector2 tempFeet, tempHead;

		ImU32 color = Render::FtIM(Settings::drawColor_box);

		if (Utils::WorldToScreen(head, tempHead) && Utils::WorldToScreen(feet, tempFeet)) {
			float height = (tempHead.y - tempFeet.y);
			float width = height / 4.0f;

			float Entity_x = tempFeet.x - width;
			float Entity_y = tempFeet.y;
			float Entity_w = height / 2;

			if (isSameTeam) color = Render::FtIM(Settings::drawColor_friendly);

			switch (Settings::typeBox) {
			case 0:	Render::DrawBox(ImVec2(Entity_x, Entity_y), ImVec2(Entity_w, height), color); break;
			case 1: Render::DrawCornerBox(ImVec2(Entity_x, Entity_y), ImVec2(Entity_w, height), color); break;
			case 2: Render::DrawFilledBox(ImVec2(Entity_x, Entity_y), ImVec2(Entity_w, height), color); break;
			}
		}
	}

	void _fastcall DrawHealthBar(uint64_t player, float health) {
		Vector3 head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.2, 0));
		Vector3 feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;

		Vector2 tempHead, tempFeet;

		if (Utils::WorldToScreen(head, tempHead) && Utils::WorldToScreen(feet, tempFeet)) {
			float height = (tempHead.y - tempFeet.y);
			float width = height / 4.0f;

			float Entity_x = tempFeet.x - width;
			float Entity_y = tempFeet.y;
			float Entity_w = height / 2;

			bool npc = false;
			int health = (int)localPlayer->Player->health;
			float maxheal = (npc ? 300.f : 100.f);
			float minheal = (npc ? 300.f : 100.f);

			//Render::DrawFilledBox(ImVec2((tempFeet.x + (width / 8.f)) - 5, Entity_y), ImVec2(Entity_w, height * (health / maxheal)), Render::FtIM(Settings::drawColor_box));
		}
	}

	void _fastcall DrawPlayerName(uint64_t player, std::string buffer, int distance) {
		Vector3 Head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.23, 0));
		Vector3 Feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
		Vector2 tempFeet;
		Vector2 tempHead;

		wchar_t res[256];
		std::string full_str = buffer + " - " + std::to_string(distance) + "m";

		if (Utils::WorldToScreen(Feet, tempFeet) && Utils::WorldToScreen(Head, tempHead)) {
			auto text_size = ImGui::CalcTextSize(full_str.c_str());

			Render::Text(ImVec2(tempFeet.x - text_size.x / 2, tempHead.y - text_size.y), full_str, Render::FtIM(Settings::drawColor_name), true, Overlay::playerName);
		}
	}

	void _fastcall DrawPlayerHealth(uint64_t player, float health) {
		Vector3 Head = (Utils::GetBonePosition(player, BonesList::l_foot) + Vector3(0, 0.23, 0));
		Vector3 Feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
		Vector2 tempFeet;
		Vector2 tempHead;

		std::string full_str = std::to_string(health) + "hp";

		if (Utils::WorldToScreen(Feet, tempFeet) && Utils::WorldToScreen(Head, tempHead)) {
			auto text_size = ImGui::CalcTextSize(full_str.c_str());

			Render::Text(ImVec2(tempFeet.x - text_size.x / 2, tempHead.y - text_size.y), full_str, Render::FtIM(Settings::drawColor_health), true, Overlay::playerName);
		}
	}

	void _fastcall DrawCurrentWeapon(uint64_t player, std::string buffer) {
		Vector3 Feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
		Vector2 tempFeet;

		if (Utils::WorldToScreen(Feet, tempFeet)) {
			auto text_size = ImGui::CalcTextSize(buffer.c_str());

			Render::Text(ImVec2(tempFeet.x - text_size.x / 2, tempFeet.y - text_size.y), buffer, ImColor(255, 255, 255), true, Overlay::playerName);
		}
	}

	void __fastcall DrawCrosshair() {
		float midX = screenWidth / 2;
		float midY = screenHeight / 2;

		Render::Line({ midX, (midY - 8) }, { midX, (midY - 4) }, Render::FtIM(Settings::drawColor_crosshair), 1.1f);
		Render::Line({ (midX - 8), midY }, { (midX - 4), midY }, Render::FtIM(Settings::drawColor_crosshair), 1.1f);

		Render::Line({ midX, (midY + 8) }, { midX, (midY + 4) }, Render::FtIM(Settings::drawColor_crosshair), 1.1f);
		Render::Line({ (midX + 8), midY }, { (midX + 4), midY }, Render::FtIM(Settings::drawColor_crosshair), 1.1f);
	}

	void __fastcall Nigger()
	{
		float xs = screenWidth / 2;
		float ys = screenHeight / 2;

		ImVec2 top = ImVec2(xs, ys + 10);
		ImVec2 right = ImVec2(xs + 10, ys);
		ImVec2 bottom = ImVec2(xs, ys - 10);
		ImVec2 left = ImVec2(xs - 10, ys);

		Render::Line({ xs, ys - 11 }, { xs, ys + 11}, Render::FtIM(Settings::drawColor_crosshair), 2.3f);
		Render::Line({ xs - 11, ys}, { xs + 11, ys }, Render::FtIM(Settings::drawColor_crosshair), 2.3f);

		Render::Line(top, { top.x + 10, top.y }, Render::FtIM(Settings::drawColor_crosshair), 2.3f);
		Render::Line(right, { right.x, right.y - 10 }, Render::FtIM(Settings::drawColor_crosshair), 2.3f);
		Render::Line(bottom, { bottom.x - 10, bottom.y }, Render::FtIM(Settings::drawColor_crosshair), 2.3f);
		Render::Line(left, { left.x, left.y + 10 }, Render::FtIM(Settings::drawColor_crosshair), 2.3f);


	}
}