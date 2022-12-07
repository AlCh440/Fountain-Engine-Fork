#pragma once
#include "../../ui_item.h"
#include "../../ModuleEngineUI.h"
#include <src/modules/Render/RendererTypes.h>
#include <src/Application.h>
class SceneView : UI_Item {
	GPUFBO fb;
public:
	SceneView() : UI_Item("Scene View") {};
	void Start();
	void Update();


	// prolly shouldnt be there but f it
	//Entity* entitySelected;

	void CleanUp();
};

class GameView : UI_Item {
	GPUFBO fb;
public:
	GameView() : UI_Item("Game View") {};
	void Start();
	void Update();


	// prolly shouldnt be there but f it
	//Entity* entitySelected;

	void CleanUp();
};