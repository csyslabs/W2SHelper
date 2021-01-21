#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <DxErr.h> //get error from error code
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

class Draw
{
public:
	/*
	IDirect3D9Ex* d3dObject = NULL;  //used to create device
	IDirect3DDevice9Ex* d3dDevice = NULL;  //contains functions like begin and end scene
	D3DPRESENT_PARAMETERS d3dparams;  //parameters for creating device
	ID3DXFont* d3dFont = 0;   // font used when displaying text
	*/
	static void Initial(HWND overlayHWND);

	static int Red;
	static int White;
	static int Orange;
	static int Yellow;
	static int Miku;
	static int Green;

	static void Render();
	static void Text(char* String, int x, int y, int a, int r, int g, int b);
	static void String(int x, int y, const char* string, D3DCOLOR color);
	static void Rect(int x, int y, int width, int height, D3DCOLOR color);
	static void BorderedRect(int x, int y, int width, int height, int fa, int fr, int fg, int fb, D3DCOLOR color);
	static void Line(int x, int y, int x1, int y2, D3DCOLOR color);
	static void HealthBar(int x, int y, int width, int height, float health, float maxHealth, D3DCOLOR color);
	static void Circle(int x, int y, int radius, D3DCOLOR color);
};

// T: specific typename		A: additional string
template <typename T>
const char* mergeString(T origin, const char* A)
{
	std::stringstream ss;
	ss << std::to_string((int)origin) << A;
	return ss.str().c_str();
}