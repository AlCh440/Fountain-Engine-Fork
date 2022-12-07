#include "SceneView.h"
#include <src/Application.h>
#include <glew/include/GL/glew.h>

void SceneView::Start() {

	//App->renderer3D->LoadFromPath((char*)"Assets/Project_1/Assets/Models/baker_house.fbx");
	fb.Create(App->window->w, App->window->h);
	App->renderer3D->hijack_framebuffer = &fb;

	
}

void SceneView::Update() {
	ImGui::Begin(name.c_str(), &active);
	ImVec2 scenesize = { (float)fb.attachment.w, (float)fb.attachment.h };
	float ww = ImGui::GetContentRegionAvail().x;
	scenesize.y /= fb.attachment.w / ww;
	scenesize.x = ww;
	ImGui::Image((ImTextureID)fb.attachment.img_id, scenesize, { 0,1 }, { 1,0 });
	ImGui::End();

	ImGui::Begin("Action Controls", nullptr, ImGuiWindowFlags_None);

	ImGui::SetCursorPos(ImVec2(scenesize.x / 2 - 60, 28));
	// Start
	if (ImGui::Button("Start", ImVec2(50, 20)))
	{
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Action Start");
	}

	ImGui::SameLine();

	// Pause
	if (ImGui::Button("Pause", ImVec2(50, 20)))
	{
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Action Paused");
	}

	ImGui::SameLine();

	// Stop
	if (ImGui::Button("Stop", ImVec2(50, 20)))
	{
	}
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip("Action Stop");
	}

	if (ImGui::Button("gameView", ImVec2(50, 20)))
	{
		App->renderer3D->gameViewOn = true;
	}

	if (ImGui::Button("cameraView", ImVec2(100, 20)))
	{
		App->renderer3D->gameViewOn = false;
	}

	ImGui::End();


}


void SceneView::CleanUp() {
	fb.Destroy();
}

