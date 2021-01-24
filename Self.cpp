#include "framework.h"

uintptr_t	Self::address;
float		Self::health;
float		Self::maxHealth;
vec3d_f		Self::worldCoords;
vec3d_f		Self::opCoords;
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

void Self::GetOpCoords()
{
	uintptr_t temp = Game::moduleBase;
	for (int i = 0; i < 2; i++) {
		temp = Memory::Read<uintptr_t>(temp + Offset::opCoordX_offModule[i]);
	}
	opCoords.x = Memory::Read<float>(temp + Offset::opCoordX_offModule[2]);
	opCoords.y = Memory::Read<float>(temp + Offset::opCoordX_offModule[2] + 0x4);
	opCoords.z = Memory::Read<float>(temp + Offset::opCoordX_offModule[2] + 0x8);
}


void Self::GetLocalPlayer()
{
	uintptr_t temp = Game::moduleBase;
	for (int i = 0; i < 3; i++) {
		temp = Memory::Read<uintptr_t>(temp + Offset::localPlayer_offModule[i]);
	}
	address = temp;
}

void Self::GetViewMatrix()
{
	// ??
	//viewMatrix = Memory::Read<float>(Game::moduleBase + Offset::viewmatrix_offModule);
	ReadProcessMemory(Game::procHandle, (LPCVOID)(Game::moduleBase + Offset::viewmatrix_offModule), &viewMatrix, sizeof(viewMatrix), nullptr);
}
