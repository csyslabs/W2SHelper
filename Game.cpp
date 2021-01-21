#include "framework.h"

// window
const LPCSTR	Game::winName = "DOOMEternal";
HWND			Game::winHWND;

int				Game::left;
int				Game::right;
int				Game::top;
int				Game::bottom;

int				Game::width;
int				Game::height;

// process
const wchar_t* Game::procName = L"DOOMEternalx64vk.exe";
HANDLE			Game::procHandle;
DWORD			Game::procId;
uintptr_t		Game::moduleBase;	
uintptr_t		Game::moduleSize;


void Game::GetProcId() {
	winHWND = FindWindowA(nullptr, winName);
	GetWindowThreadProcessId(winHWND, &procId);
}

void Game::GetProcHandle() {
	procHandle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE, false, procId);
}

void Game::GetWindowInfo() {
	RECT rect;
	GetWindowRect(winHWND, &rect);

	left = rect.left, right = rect.right, top = rect.top, bottom = rect.bottom;

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
}

void Game::GetModuleBase()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	//QWORD dwModuleBaseAddress = 0;
	uintptr_t modBaseAddr = 0;
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ME32;
		ME32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &ME32))
		{
			do
			{
				if (!_wcsicmp(ME32.szModule, procName))
				{
					modBaseAddr = (uintptr_t)ME32.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnapshot, &ME32));
		}
	}
	moduleBase = modBaseAddr;
	CloseHandle(hSnapshot);
}