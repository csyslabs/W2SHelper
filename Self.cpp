#include "framework.h"

uintptr_t	Self::address;
float		Self::health;
float		Self::maxHealth;
vec3d_f		Self::worldCoords;
vec2d_f		Self::screenCoords;
float		Self::viewMatrix[16];

void Self::GetHealth()
{
	health = Memory::Read<float>(address + Offset::health_offEntity);
}

void Self::GetWorldCoords()
{
	worldCoords.x = Memory::Read<float>(address + Offset::coordX_offEntity);
	worldCoords.y = Memory::Read<float>(address + Offset::coordY_offEntity);
	worldCoords.z = Memory::Read<float>(address + Offset::coordZ_offEntity);
}

void Self::GetBasicInfo()
{
	address = Memory::Read<uintptr_t>(Game::moduleBase + Offset::localPlayer_offModule);
}

void Self::GetViewMatrix()
{
	// ??
	//viewMatrix = Memory::Read<float>(Game::moduleBase + Offset::viewmatrix_offModule);
	ReadProcessMemory(Game::procHandle, (LPCVOID)(Game::moduleBase + Offset::viewmatrix_offModule), &viewMatrix, sizeof(viewMatrix), nullptr);
}
