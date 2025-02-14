#include "CS_Transform.h"
#include <src/modules/EngineUI/DearImGUI/imgui.h>

#include "src/helpers/C_AABB.h"

static char headerid[64];
static bool world_t = false;
static Quat temp_quat;
static float3 temp_rot, prev_rot;
static float3 temp_pos, prev_pos;
static float3 temp_scale, prev_scale;

void C_Transform::PropagateChanges() {
	Entity* parent = id.parent;
	for (Entity* child : parent->children) {
		C_Transform* child_t = child->GetComponent<C_Transform>();
		if (child_t != NULL) {
			child_t->world_mat = world_mat * local_mat;
			child_t->PropagateChanges();
		}
	}
}

void C_Transform::NotifyBoundingBox()
{
	Entity* gameObject = GetGameObject(id.parent);
	
	//C_AABB* child_t = parent->GetComponent<C_AABB>();
	//if (child_t)
	//	child_t->aabb->Transform(world_mat * local_mat);
	if (gameObject != NULL)
	{
		for (Entity* child : gameObject->children) {
			if (C_AABB* child_t = child->GetComponent<C_AABB>())
			{
				child_t->UpdateBoundingBox(temp_pos, prev_rot, prev_scale);
			}

		}
	}
}

void C_Transform::NotifyCamera()
{
	Entity* gameObject = GetGameObject(id.parent);

	//C_AABB* child_t = parent->GetComponent<C_AABB>();
	//if (child_t)
	//	child_t->aabb->Transform(world_mat * local_mat);
	if (gameObject != NULL)
	{
		for (Entity* child : gameObject->children) {
			if (C_camera* child_t = child->GetComponent<C_camera>())
			{
				vec3 mov(temp_pos.x, temp_pos.y, temp_pos.z);

				child_t->Move(mov);
			}

		}

		if (C_camera* child_t = gameObject->GetComponent<C_camera>())
		{
			vec3 mov(temp_pos.x, temp_pos.y, temp_pos.z);

			child_t->Move(mov);
		}
	}

	if (C_camera* child_t = id.parent->GetComponent<C_camera>())
	{
		vec3 mov(temp_pos.x, temp_pos.y, temp_pos.z);

		child_t->Move(mov);
	}
}

Entity* C_Transform::GetGameObject(Entity* child) {
	Entity* parent = child->parent;
	if (parent != NULL)
	{
		if (parent->isGameObject == true)
		{
			return parent;
		}

		return GetGameObject(parent);
	}
	else
	{
		return NULL;
	}
	
	
}
void C_Transform::DrawInspector() {
	bool changed = false;

	sprintf(headerid, "Transform##%llu", id.id);
	if (ImGui::CollapsingHeader(headerid)) {
		sprintf(headerid, "STATIC##%llu", id.id);
		ImGui::Checkbox(headerid, &is_static);
		ImGui::SameLine();
		sprintf(headerid, "RESET##llu", id.id);
		if (ImGui::Button(headerid)) {
			local_mat = float4x4::identity;
			//NotifyBoundingBox();
			PropagateChanges();
		}
		if (ImGui::RadioButton("World", world_t)) world_t = !world_t;
		ImGui::SameLine();
		if (ImGui::RadioButton("Local", !world_t)) world_t = !world_t;

		float4x4 use_mat = (world_t) ? world_mat * local_mat : local_mat;
		use_mat.Decompose(temp_pos, temp_quat, temp_scale);
		
		prev_pos = temp_pos;
		prev_rot = temp_rot = temp_quat.ToEulerXYZ();
		prev_scale = temp_scale;
		sprintf(headerid, "POSITION##%llu", id.id);
		changed |= ImGui::DragFloat3(headerid, temp_pos.ptr(), .2f);
		sprintf(headerid, "ROTATION##%llu", id.id);
		changed |= ImGui::DragFloat3(headerid, temp_rot.ptr(), .1f);
		sprintf(headerid, "SCALE##%llu", id.id);
		changed |= ImGui::DragFloat3(headerid, temp_scale.ptr(), .2f);

		if (changed) {
			temp_pos -= prev_pos; 
			temp_rot -= prev_rot; 
			temp_quat = Quat::FromEulerXYZ(temp_rot.x, temp_rot.y, temp_rot.z);
			temp_scale -= prev_scale;
			
			Quat prev_quat;
			local_mat.Decompose(prev_pos, prev_quat, prev_scale);
			prev_pos += temp_pos;
			prev_quat = temp_quat.Mul(prev_quat);
			prev_scale += temp_scale;
			
			// Check no smaller than 0.01f, Mathgeolib limit
			prev_scale.x = (prev_scale.x < 0.01f) ? 0.01f : prev_scale.x;
			prev_scale.y = (prev_scale.y < 0.01f) ? 0.01f : prev_scale.y;
			prev_scale.z = (prev_scale.z < 0.01f) ? 0.01f : prev_scale.z;
			

			local_mat = float4x4::FromTRS(prev_pos, prev_quat, prev_scale);
			
			PropagateChanges();
			NotifyBoundingBox();
			NotifyCamera();
		}
	}
}