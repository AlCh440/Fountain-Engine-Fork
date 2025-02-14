#include <src/helpers/Globals.h>
#include <src/Application.h>
#include "ModuleCamera3D.h"

C_camera::C_camera(bool start_enabled) 
{
	id.ctype = CT_CAMERA; id.id = PCGRand();

	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 0.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
}

C_camera::~C_camera()
{}

// -----------------------------------------------------------------
void C_camera::Start()
{
	PLOG("Setting up the camera");
	bool ret = true;

	
}

// -----------------------------------------------------------------
void C_camera::CleanUp()
{
	PLOG("Cleaning camera");

	
}

// -----------------------------------------------------------------
void C_camera::Update(float dt)
{
	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	vec3 newPos(0,0,0);
	float speed = 3.0f * dt;
	if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 8.0f * dt;

	if (playerOn) 
	{ 
		if (App->renderer3D->gameViewOn) {


			if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) newPos.y += speed;
			if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) newPos.y -= speed;

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * speed;
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Z * speed;


			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * speed;
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * speed;
			Position += newPos;
			Reference += newPos;

			// Mouse motion ----------------

			if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
			{
				int dx = -App->input->GetMouseXMotion();
				int dy = -App->input->GetMouseYMotion();

				float Sensitivity = 0.25f;

				Position -= Reference;

				if (dx != 0)
				{
					float DeltaX = (float)dx * Sensitivity;

					X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
					Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
					Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				}

				if (dy != 0)
				{
					float DeltaY = (float)dy * Sensitivity;

					Y = rotate(Y, DeltaY, X);
					Z = rotate(Z, DeltaY, X);

					if (Y.y < 0.0f)
					{
						Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
						Y = cross(Z, X);
					}
				}

				Position = Reference + Z * length(Position);
			}

			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
				
			}
		}
	}
	else
	{
		if (!App->renderer3D->gameViewOn) {
			if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) newPos.y += speed;
			if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) newPos.y -= speed;

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * speed;
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Z * speed;


			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * speed;
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * speed;

			Position += newPos;
			Reference += newPos;

			// Mouse motion ----------------

			if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
			{
				int dx = -App->input->GetMouseXMotion();
				int dy = -App->input->GetMouseYMotion();

				float Sensitivity = 0.25f;

				Position -= Reference;

				if (dx != 0)
				{
					float DeltaX = (float)dx * Sensitivity;

					X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
					Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
					Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
				}

				if (dy != 0)
				{
					float DeltaY = (float)dy * Sensitivity;

					Y = rotate(Y, DeltaY, X);
					Z = rotate(Z, DeltaY, X);

					if (Y.y < 0.0f)
					{
						Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
						Y = cross(Z, X);
					}
				}

				Position = Reference + Z * length(Position);
			}
		}
	}

	

	

	// Recalculate matrix -------------
	CalculateViewMatrix();

}

// -----------------------------------------------------------------
void C_camera::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void C_camera::LookAt( const vec3 &Spot)
{
	Reference = Spot;
	
	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void C_camera::Move(const vec3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* C_camera::GetViewMatrix()
{
	return &ViewMatrix;
}

// -----------------------------------------------------------------
void C_camera::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}