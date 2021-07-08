#pragma once
#include "Overlay.hpp"
#include "../SDK/Imports.hpp"
#include "Settings.hpp"

void AimbotTab()
{
	ImGui::BeginChild(safe_str("Aimbot"), ImVec2(170, 248), true);
	{
		ImGui::Checkbox(safe_str("Enable "), &Settings::enableAimbot);
		ImGui::Hotkey(safe_str("##On Key"), &Settings::aimbotKey, ImVec2(100, 20));
	} ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild(safe_str("Settings"), ImVec2(506, 248), true);
	{
		ImGui::SliderFloat5(safe_str("Aimbot FOV"), &Settings::aimbotFov, 1, 360, safe_str("%.2f"));
		//ImGui::Checkbox(safe_str("thick bullet"), &Settings::night_mode);
	} ImGui::EndChild();
}

void VisualsTab()
{                                           //238 //248
	ImGui::BeginChild(safe_str("ESP"), ImVec2(480, 248), true);
	{
		ImGui::Checkbox(safe_str("Player Box"), &Settings::drawBox); ImGui::ColorEdit4(safe_str("Box Color"), Settings::drawColor_box, ImGuiColorEditFlags_NoInputs);
		if (Settings::drawBox) {
			ImGui::Combo(safe_str("Box Type"), &Settings::typeBox, Settings::boxTypes, 3);
			ImGui::SliderInt5(safe_str("Distance##Distance1"), &Settings::boxDistance, 100, 300);
		}

		ImGui::Checkbox(safe_str("Health"), &Settings::drawHealthBar), ImGui::ColorEdit4(safe_str("Health Color"), Settings::drawColor_health, ImGuiColorEditFlags_NoInputs);
		if (Settings::drawHealthBar)
			ImGui::SliderInt5(safe_str("Distance##Distance2"), &Settings::healthDistance, 100, 300);

		ImGui::Checkbox(safe_str("Skeleton"), &Settings::drawSkeleton); ImGui::ColorEdit4(safe_str("Skeleton Color"), Settings::drawColor_skeleton, ImGuiColorEditFlags_NoInputs);
		if (Settings::drawSkeleton)
			ImGui::SliderInt5(safe_str("Distance##Distance3"), &Settings::skeletonDistance, 100, 300);

		ImGui::Checkbox(safe_str("Name"), &Settings::drawName); ImGui::ColorEdit4(safe_str("Name Color"), Settings::drawColor_name, ImGuiColorEditFlags_NoInputs);
		if (Settings::drawName)
			ImGui::SliderInt5(safe_str("Distance##Distance4"), &Settings::nameDistance, 100, 300);

		ImGui::Checkbox(safe_str("Crosshair"), &Settings::drawCrosshair); ImGui::ColorEdit4(safe_str("Crosshair Color"), Settings::drawColor_crosshair, ImGuiColorEditFlags_NoInputs);

		if (Settings::drawCrosshair)
		{
			ImGui::Checkbox("while scoped", &Settings::crosshairScoped);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
			ImGui::SliderInt("Length", &Settings::CrosshairLength, 1, 24);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
			ImGui::SliderInt("Gap", &Settings::CrosshairGap, 0, 24);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
			ImGui::SliderInt("Thickness", &Settings::CrosshairThickness, 1, 24);
		}

		ImGui::Checkbox(safe_str("Niggers"), &Settings::niggerCross); ImGui::ColorEdit4(safe_str("Crosshair Color"), Settings::drawColor_crosshair, ImGuiColorEditFlags_NoInputs);


		ImGui::SliderFloat5(safe_str("Fov Changer"), &Settings::FovSlider, 90, 150);

		if (ImGui::BeginCombo(safe_str("Resources"), safe_str("")))
		{
			for (size_t i = 0; i < IM_ARRAYSIZE(Settings::selectedOres); i++) {
				ImGui::Selectable(Settings::oresItems[i], &Settings::selectedOres[i], ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
			}

			ImGui::EndCombo();
		}
	} ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild(safe_str("OtherESP"), ImVec2(195, 248), true);
	{
	}ImGui::EndChild();
}

void MiscTabb()
{                                             //476
	ImGui::BeginChild(safe_str("Misc"), ImVec2(680, 248), true);
	{
		ImGui::Text(safe_str("Weapon Options"));
		//ImGui::Checkbox(safe_str("Shoot in the Air"), &Settings::shootInAir);
		ImGui::Checkbox(safe_str("Rapid Fire"), &Settings::rapidFire);
		if (Settings::rapidFire)
		{
			ImGui::SliderFloat5(safe_str("Rapid Fire Value"), &Settings::rapidfirevalue, 0.01, 0.09);
		}
		ImGui::Checkbox(safe_str("No Recoil"), &Settings::noRecoil);
		ImGui::Checkbox(safe_str("Instant Compound"), &Settings::instantCompound);
		ImGui::Checkbox(safe_str("Instant Switch"), &Settings::fastSwitchWeapons);

		ImGui::Separator();

		ImGui::Text(safe_str("Player Options"));
		if (Settings::infinateJump)
		{
			ImGui::Hotkey(safe_str("##On Key1"), &Settings::jumpKey, ImVec2(100, 20));
		}
		ImGui::Checkbox(safe_str("Spider Climb"), &Settings::spiderClimb);

		ImGui::Checkbox(safe_str("Speedhack"), &Settings::speedhack);
		ImGui::SameLine();
		if (Settings::speedhack)
		{
			ImGui::Hotkey(safe_str("##On Key2"), &Settings::speedHackkey, ImVec2(100, 20));
		}
		ImGui::Checkbox(safe_str("Walk On Water"), &Settings::walkOnWater);
		ImGui::SameLine();
		if (Settings::walkOnWater)
		{
			ImGui::Hotkey(safe_str("##On Key3"), &Settings::walkWaterKEY, ImVec2(100, 20));
		}
		ImGui::Checkbox(safe_str("admin flag"), &Settings::adminFlag);

		ImGui::Checkbox(safe_str("instant eoka"), &Settings::tapeoka);
		ImGui::Checkbox(safe_str("third person"), &Settings::thirdperson);
		ImGui::Checkbox(safe_str("Long Neck"), &Settings::shootInAir);
		ImGui::SameLine();
		if (Settings::shootInAir)
		{
			ImGui::Hotkey(safe_str("##On Key1"), &Settings::LongNeckKey, ImVec2(100, 20));
		}

		/*ImGui::Checkbox(safe_str("Freeze Player"), &Settings::freeze);
		if (Settings::freeze)
		{
			ImGui::Hotkey(safe_str("##On Key1"), &Settings::flyKey, ImVec2(100, 20));
		}*/

	} ImGui::EndChild();
}

void __fastcall DrawMenu()
{
	ImGui::SetNextWindowSize(ImVec2(screenWidth, screenHeight));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowBgAlpha(.5f);

	ImGui::Begin(safe_str("Background"), (bool*)true, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove);
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.568, 0.533, 0.533, .2f));
		ImGui::PopStyleColor();
		ImGui::End();
	}

	//Window Size
	ImGui::SetNextWindowSize(ImVec2(700, 330));
	ImGui::SetNextWindowPos(ImVec2((1920 - 840) * .5, (1080 - 500) * .5), ImGuiCond_Once);

	ImGui::Begin(safe_str("Havok"), (bool*)true, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	{
		ImGui::SetScrollY(0);

		ImVec2 p = ImGui::GetCursorScreenPos();
		ImColor c = ImColor(32, 114, 247);

		//Nav bar
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x, p.y + 30), ImVec2(p.x + ImGui::GetWindowWidth(), p.y - 3), ImColor(25, 20, 36, 255));
		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(p.x, p.y + 32), ImVec2(p.x + ImGui::GetWindowWidth(), p.y + +30), ImColor(255, 34, 0, 255),
			ImColor(255, 34, 0, 255), ImColor(255, 34, 0, 255), ImColor(255, 34, 0, 255));

		ImGui::SameLine();

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8);
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3);
		ImGui::Text(safe_str("Havok.cc"));

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.117f, 0.117f, 0.152f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(78 / 255.f, 78 / 255.f, 87 / 255.f, 1));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.117, 0.117, 0.152, 1));
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.5f));

		ImGui::SameLine(0, 0);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5); //5
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 430); //272 - this part moves the | text Higher = right   Lower = left

		static int page = 0;

		if (ImGui::ButtonT(safe_str("Aimbot"), ImVec2(50, 25), page, 0, false, false)) page = 0; ImGui::SameLine(0, 0);
		if (ImGui::ButtonT(safe_str("Visuals"), ImVec2(50, 25), page, 1, false, false)) page = 1; ImGui::SameLine(0, 0);
		if (ImGui::ButtonT(safe_str("Misc"), ImVec2(40, 25), page, 2, false, false)) page = 2; ImGui::SameLine(0, 0);

		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();

		ImGui::SetCursorPosY(9);

		ImGui::Dummy(ImVec2(0, 25));
		ImGui::Dummy(ImVec2(0, 0)); ImGui::SameLine();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(16, 16));

		ImGui::PushFont(Overlay::fontMenu);

		switch (page)
		{
		case 0:
			AimbotTab(); break;
		case 1:
			VisualsTab(); break;
		case 2:
			MiscTabb(); break;

			/*case 3:
				skins_tab(); break;
			case 4:
				settings_tab(); break; */
		}
		ImGui::PopFont();

		ImGui::PopStyleVar();

		ImGui::SetCursorPosY(305);
		ImVec2 p2 = ImGui::GetCursorScreenPos();

		//Footer
		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(p2.x, p2.y + -5), ImVec2(p2.x + ImGui::GetWindowWidth(), p2.y + +30), ImColor(255, 34, 0, 255), ImColor(255, 34, 0, 255), ImColor(255, 34, 0, 255), ImColor(255, 34, 0, 255));
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p2.x, p2.y + 30), ImVec2(p2.x + ImGui::GetWindowWidth(), p2.y - 3), ImColor(25, 20, 36, 255));

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 650); //465
		ImGui::Text(safe_str("Rust"));

		ImGui::End();
	}
}