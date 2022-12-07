#pragma once

#include "../../ui_item.h"
#include "../../ModuleEngineUI.h"
#include <filesystem>

constexpr char* s_AssetPath = "Assets";

class RenderPeekWindow : UI_Item {
public:
	//RenderPeekWindow() : UI_Item("PeekRenderData") {};
	RenderPeekWindow() : UI_Item("Assets") { m_CurrentDirectory = s_AssetPath; };
	void Start();

	void Update();

private:
	int t_w = 500;

	std::filesystem::path m_CurrentDirectory;
	SDL_Surface* icon;
};