#pragma once

class Self
{
public:
	static uintptr_t address;
	static float health;
	static float maxHealth;
	static vec3d_f worldCoords;
	static vec3d_f opCoords;
	static vec2d_f screenCoords;
	static void GetHealth();
	static void GetWorldCoords();
	static void GetOpCoords();
	// self specific info
	static float viewMatrix[16];
	static void GetLocalPlayer();
	static void GetViewMatrix();
};

