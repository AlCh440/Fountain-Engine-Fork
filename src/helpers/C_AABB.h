#pragma once

#include "src/modules/ECS/ModuleECS.h"
//#include <src/helpers/MathGeoLib/MathGeoLib.h>
#include <src/Application.h>

struct C_AABB : public Component {
	constexpr static ComponentTypes type = CT_AABB;
	C_AABB() { id.ctype = CT_AABB; id.id = PCGRand(); }

	AABB* aabb;
	
	void Init() override {

	};

	void Start() override {

	};

	void PostUpdate(float dt) override {
		aabb->Draw();
	};

	void UpdateBoundingBox(float3 pos, float3 rot, float3 scale) {
		float3 center = aabb->CenterPoint();
		center += pos;
		aabb->SetFromCenterAndSize(center, aabb->Size());
	};

};