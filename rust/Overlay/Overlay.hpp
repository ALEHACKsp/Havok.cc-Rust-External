#pragma once
#include "imgui/imgui.h"
#include <string>

namespace ESP
{
	void __fastcall Run();
}

namespace Overlay
{
	void __fastcall Loop();
	void Style();
	inline ImFont* fontTitle;
	inline ImFont* fontMenu;
	inline ImFont* playerName;
}

namespace Render
{
	void __fastcall Line(ImVec2 pos, ImVec2 size, ImU32 color, float thickness);
	void __fastcall DrawBox(ImVec2 pos, ImVec2 size, ImColor color);
	void __fastcall DrawFilledBox(ImVec2 pos, ImVec2 size, ImColor color);
	void __fastcall DrawCornerBox(ImVec2 pos, ImVec2 size, ImColor color);
	void __fastcall Text(ImVec2 pos, std::string strText, ImColor color, bool outline, ImFont* font, float fontSize = 0.f);
	void __fastcall Circle(ImVec2 point, float radius, ImColor color);
	void __fastcall DrawHealthBar(ImVec2 pos, ImVec2 size, ImColor color);
	ImU32 __fastcall FtIM(float* a_value);
}