#pragma once

class Game
{
public:
	// window
	static const LPCSTR			winName;
	static HWND					winHWND;

	static int					left;
	static int					right;
	static int					top;
	static int					bottom;

	static int					width;
	static int					height;

	// process
	static const wchar_t*		procName;
	static HANDLE				procHandle;
	static DWORD procId;
	static uintptr_t			moduleBase;	
	static uintptr_t			moduleSize;

	static void GetProcId();
	static void GetProcHandle();
	static void GetWindowInfo();
	static void GetModuleBase();
};

namespace Offset
{
	// off module
	static uintptr_t localPlayer_offModule[3] = {0x616F300, 0x0, 0x18};
	static uintptr_t viewmatrix_offModule = 0x5BBD810;

	// off entity
	static uintptr_t health_offEntity = 0x280;
	static uintptr_t maxHealth_offEntity = 0x2A0;
	static uintptr_t coordX_offEntity = 0x94C;
	static uintptr_t coordY_offEntity = 0x950;
	static uintptr_t coordZ_offEntity = 0x954;
};

namespace Memory
{
	template <typename T>
	T Read(uintptr_t address)
	{
		T VALUE;
		ReadProcessMemory(Game::procHandle, (LPCVOID)(address), &VALUE, sizeof(VALUE), 0);
		return VALUE;
	}
};