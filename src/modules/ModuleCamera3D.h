#pragma once
#include <src/modules/Module.h>
#include <src/helpers/Globals.h>
#include <src/helpers/glmath.h>
#include <src/helpers/MathGeoLib/MathGeoLib.h>
#include "ECS/ComponentsIncludeAll.h"


struct C_camera : public Component
{
	constexpr static ComponentTypes type = CT_CAMERA;


	C_camera(bool start_enabled = true);
	~C_camera();

	void Start() override;
	void Update(float dt) override ;
	void CleanUp() override;

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	float* GetViewMatrix();



	void CalculateViewMatrix();

	
	vec3 X, Y, Z, Position, Reference;



	mat4x4 ViewMatrix, ViewMatrixInverse;
};