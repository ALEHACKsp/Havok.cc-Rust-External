#pragma once
#include "Overlay.hpp"
#include "../SDK/Imports.hpp"
#include "Settings.hpp"

void AimbotTab()
{
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 62);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 10);
    ImGui::BeginChild("Aimbot", ImVec2(538, 368), true);
    {
        ImGui::TextColored(ImColor(175, 0, 255, 255), ("Aimbot"));
        ImGui::Checkbox("Enable Aimbot", &Settings::enableAimbot);
        ImGui::Text("Aimbot Key"); ImGui::SameLine(); ImGui::Hotkey("##Aimbot Key", &Settings::aimbotKey, ImVec2(80, 15));

        ImGui::Spacing();
        ImGui::Checkbox("Enable Smoothing", &Settings::enableSmoothing);
        if (Settings::enableSmoothing)
        {
            ImGui::SliderFloat5(safe_str("smooth"), &Settings::aimSmoothing, 1, 100, safe_str("%.2f"));
        }
        ImGui::Spacing();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 18);
        ImGui::Spacing();
        ImGui::SliderInt5("Aimbot FOV", &Settings::aimbotFov, 0, 360);
        ImGui::SliderInt5("Aimbot Distance", &Settings::aimbotDistance, 0, 300);

        ImGui::PushItemWidth(ImGui::GetWindowWidth() - 340);
        ImGui::Spacing();
        const char* listbox_items[] = { "Head", "Chest", "Pevlis" };
        ImGui::ListBox("##Hitbox", &Settings::aimbotHitbox, listbox_items, IM_ARRAYSIZE(listbox_items));
        ImGui::Checkbox("ThickBullet", &Settings::thickBullettt);

        ImGui::PopItemWidth();

        ImGui::EndChild();
    }
}

void MiscTab()
{
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 62);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 10);
    ImGui::BeginChild("Misc", ImVec2(538, 368), true);
    {
        ImGui::TextColored(ImColor(175, 0, 255, 255), ("Weapon Options"));
        ImGui::Checkbox(("Rapid Fire"), &Settings::rapidFire);
        if (Settings::rapidFire)
        {
            ImGui::SliderFloat5(("Rapid Fire Value"), &Settings::rapidfirevalue, 0.01, 0.09);
        }
        ImGui::Checkbox(("Enable RCS"), &Settings::enableRCS);
        if (Settings::enableRCS)
        {
            ImGui::SliderInt5(("RCS Percentage X"), &Settings::RCSyaw, 0, -50, "%.0f");
            ImGui::SliderInt5(("RCS Percentage Y"), &Settings::RCSpitch, 0, -50, "%.0f");
        }
        ImGui::Checkbox(("No Spread"), &Settings::noSpread);
        ImGui::Checkbox(("Instant Compound"), &Settings::instantCompound);
        ImGui::Checkbox(("Instant Switch"), &Settings::fastSwitchWeapons);

        ImGui::Spacing();

        ImGui::TextColored(ImColor(175, 0, 255, 255), ("Player Options"));
        ImGui::Checkbox(("Spider Climb"), &Settings::spiderClimb);

        ImGui::Checkbox(("Speedhack"), &Settings::speedhack);
        if (Settings::speedhack)
        {
            ImGui::SameLine();
            ImGui::Hotkey(("##On Key2"), &Settings::speedHackkey, ImVec2(80, 15));
        }

        ImGui::Checkbox(("admin flag"), &Settings::adminFlag);
        ImGui::Checkbox(("TOD Changer"), &Settings::night_mode);
        if (Settings::night_mode)
            ImGui::SliderFloat(("Time"), &Settings::time, 0, 24);

        ImGui::Checkbox("Sky Color", &Settings::skyColorBool);
        if (Settings::skyColorBool)
            ImGui::SliderFloat("color", &Settings::SkyColor, 0, 100);


        ImGui::Checkbox(("Long Hit"), &Settings::longhit);
        ImGui::Checkbox(("instant eoka"), &Settings::tapeoka);
        ImGui::Checkbox(("third person"), &Settings::thirdperson);
        ImGui::Checkbox(("Long Neck"), &Settings::shootInAir);
        if (Settings::shootInAir)
        {
            ImGui::SameLine();
            ImGui::Hotkey(("##On Key1"), &Settings::LongNeckKey, ImVec2(80, 15));
        }
        ImGui::Checkbox("High Jump", &Settings::SuperJump);
        if (Settings::SuperJump)
        {
            ImGui::SliderFloat5("value", &Settings::GravitySlider, 10, 0);
        }
        ImGui::Checkbox("Debug Camera Fix", &Settings::DebugFix);
        ImGui::Checkbox("Hold Items While Mounted", &Settings::ShootMounted);
        ImGui::Checkbox("Sleeping Model", &Settings::debugFlag);
        ImGui::Checkbox(("Bright Night"), &Settings::nightSky);
        ImGui::Checkbox(("Run Hit"), &Settings::runhit);
        ImGui::Checkbox(("Zoom"), &Settings::zoom);
        if (Settings::zoom)
        {
            ImGui::Hotkey(("##On Key4"), &Settings::zoomKey, ImVec2(80, 15));
        }
        ImGui::Checkbox("Player Swim", &Settings::waterLevel);
        ImGui::Checkbox("Run Anywhere", &Settings::sprinttt);
        ImGui::Checkbox("Infinate Jump", &Settings::infinateJump);
        if (Settings::infinateJump)
        {
            ImGui::Hotkey(("##On Key1"), &Settings::jumpKey, ImVec2(80, 15));

        }
        ImGui::Checkbox("FlyHack", &Settings::flyHackkk);
        if (Settings::flyHackkk)
        {
            ImGui::Hotkey("##Flyhack Key", &Settings::flyhackKey, ImVec2(80, 15));
            ImGui::SliderFloat5(("speed"), &Settings::flyhackSpeed, 2, -200);
        }
        
        ImGui::EndChild();
    }
}
const char* boxTypes[] = { ("Static Box"), ("Corner Box"), ("Filled Box") };
const char* oresItems[] = {
    "Stone Ore",
    "Metal Ore",
    "Sulfur Ore",
    "Stone Collectable",
    "Metal Collectable",
    "Sulfur Collectable",
    "Wood Collectable",
    "Hemp Fibers",
    "Stash",
    "Barrel",
    "Oil Barrel",
    "Elite Crate",
    "Military Crate",
    "Medical Crate",
    "Normal Crate",
    "Food Crate",
    "Tool Box",
    "Boat",
    "RHIB",
    "kayak",
    "Minicopter",
    "Bradley" };
void VisualTab()
{
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 62);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 10);
    ImGui::BeginChild("Visuals", ImVec2(538, 368), true);
    {
        ImGui::Checkbox("Enable Visuals", &Settings::enableVisuals);
        ImGui::Spacing();

        ImGui::Checkbox(("Player Box"), &Settings::drawBox); ImGui::ColorEdit4(("Box Color"), Settings::drawColor_box, ImGuiColorEditFlags_NoInputs);
        if (Settings::drawBox) {
            ImGui::Combo(("Box Type"), &Settings::typeBox, boxTypes, 3);
            ImGui::SliderInt5(("Distance##Distance1"), &Settings::boxDistance, 100, 300);
        }

        ImGui::Checkbox(("Weapon ESP"), &Settings::drawWeapon);
        if (Settings::drawWeapon)
            ImGui::SliderInt5(("Distance##Distance123798"), &Settings::weaponDistance, 100, 300);
        

        ImGui::Checkbox(("Health"), &Settings::drawHealthBar), ImGui::ColorEdit4(("Health Color"), Settings::drawColor_health, ImGuiColorEditFlags_NoInputs);
        if (Settings::drawHealthBar)
            ImGui::SliderInt5(("Distance##Distance2"), &Settings::healthDistance, 100, 300);
        

        ImGui::Checkbox(("Skeleton"), &Settings::drawSkeleton); ImGui::ColorEdit4(("Skeleton Color"), Settings::drawColor_skeleton, ImGuiColorEditFlags_NoInputs);
        if (Settings::drawSkeleton)
            ImGui::SliderInt5(("Distance##Distance3"), &Settings::skeletonDistance, 100, 300);
        

        ImGui::Checkbox(("Name"), &Settings::drawName); ImGui::ColorEdit4(("Name Color"), Settings::drawColor_name, ImGuiColorEditFlags_NoInputs);
        if (Settings::drawName)
            ImGui::SliderInt5(("Distance##Distance4"), &Settings::nameDistance, 100, 300);
        

        ImGui::Checkbox(("Dead Players"), &Settings::corpseESP);
        if (Settings::corpseESP)
            ImGui::SliderInt5(("Distance##Distance34"), &Settings::corpseESPdistance, 100, 300);
        

        ImGui::Checkbox(("Crosshair"), &Settings::drawCrosshair); ImGui::ColorEdit4(("Crosshair Color"), Settings::drawColor_crosshair, ImGuiColorEditFlags_NoInputs);
        if (Settings::drawCrosshair)
        {
            ImGui::Checkbox("while scoped", &Settings::crosshairScoped);
            ImGui::SliderInt5("Length", &Settings::CrosshairLength, 1, 24);
            ImGui::SliderInt5("Gap", &Settings::CrosshairGap, 0, 24);
            ImGui::SliderInt5("Thickness", &Settings::CrosshairThickness, 1, 24);
        }

        ImGui::SliderInt5(("Fov Changer"), &Settings::FovSlider, 75, 150);
        ImGui::Checkbox("Test", &Settings::niggaDebug);


        ImGui::TextColored(ImColor(175, 0, 255, 255), "ESP Object List");
        //ImGui::PushItemWidth(300);

        ImGui::ColorEdit4(("Color"), Settings::espColorMisc, ImGuiColorEditFlags_NoInputs);
        if (ImGui::ListBoxHeader("##ESP Object List"))
        {
            for (size_t i = 0; i < IM_ARRAYSIZE(Settings::selectedOres); i++) {
                ImGui::Selectable(oresItems[i], &Settings::selectedOres[i], ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups);
            }
            ImGui::ListBoxFooter();
        }
        //ImGui::PopItemWidth();
        
        ImGui::EndChild();
    }
}

void SettingsTab()
{
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 62);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 10);
    ImGui::BeginChild("Settings", ImVec2(538, 368), true);
    {
        
        ImGui::EndChild();
    }
}
#include "../fonts/icons.h"
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
	ImGui::SetNextWindowSize(ImVec2(600, 400));
	ImGui::SetNextWindowPos(ImVec2((1920 - 840) * .5, (1080 - 500) * .5), ImGuiCond_Once);

	ImGui::Begin(safe_str("Havok"), (bool*)true, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	{
		ImGui::SetScrollY(0);

		ImVec2 p = ImGui::GetCursorScreenPos();
		ImColor barColors = ImColor(88, 0, 255, 255);

		//Topbar
		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(p.x, p.y + 32), ImVec2(p.x + ImGui::GetWindowWidth(), p.y + +30), ImColor(255, 34, 0, 255),
			barColors, barColors, barColors);
		//Sidebar
		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(p.x + 70, p.y + 32), ImVec2(p.x + 68, p.y + ImGui::GetWindowHeight()), ImColor(255, 34, 0, 255),
			barColors, barColors, barColors);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.117f, 0.117f, 0.152f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(78 / 255.f, 78 / 255.f, 87 / 255.f, 1));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.117, 0.117, 0.152, 1));
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.5f));


		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 260);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 7);
		ImGui::TextColored(ImColor(175, 0, 255, 255), "Havok.cc");//s

		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 8);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 50);

		static int page = 0;
		ImGui::PushFont(Overlay::menuIcon);
		if (ImGui::ButtonT((ICON_FA_CROSSHAIRS), ImVec2(50, 35), page, 0, false, false)) page = 0; ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 8); ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5);
		if (ImGui::ButtonT((ICON_FA_EYE), ImVec2(50, 35), page, 1, false, false)) page = 1; ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 8); ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5);
		if (ImGui::ButtonT((ICON_FA_COG), ImVec2(50, 35), page, 2, false, false)) page = 2; ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 8); ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5);
		if (ImGui::ButtonT((ICON_FA_USER), ImVec2(50, 35), page, 3, false, false)) page = 3; ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 8); ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5);
		ImGui::PopFont();

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
			VisualTab(); break;
		case 2:
			MiscTab(); break;
		case 3:
			SettingsTab(); break;
		}
		ImGui::PopFont();
		ImGui::PopStyleVar();

		ImGui::SetCursorPosY(305);
		ImVec2 p2 = ImGui::GetCursorScreenPos();
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 650);
		ImGui::Text(("Rust"));

		ImGui::End();
	}
}