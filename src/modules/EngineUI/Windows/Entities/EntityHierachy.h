#pragma once

#include "../../ui_item.h"
#include "../../ModuleEngineUI.h"
#include "../Inspector/ComponentInspector.h"
#include "../../ImGuizmo/ImGuizmo.h"


struct EntityHierarchyWindow : public UI_Item {
	EntityHierarchyWindow() : UI_Item("Enity Hierarchy") {
		rm_menu.flags = ImGuiHoveredFlags_ChildWindows || ImGuiHoveredFlags_RootWindow;
		rm_menu.container_name = name.c_str();
	};
	~EntityHierarchyWindow() {};

	void Start();
	void Update();

	RMPopupMenu rm_menu;
	void UpdateRMMenu();

	ComponentInspector* inspector = nullptr;

	std::vector<uint64_t> selected;
	bool IsSelected(uint64_t eid) { for (auto v : selected) if (eid == v) return true; return false; }
	void UpdateEntry(Entity* entity);


};