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
	static void Initial(HWND overlayHWND);

	static int Red;
	static int White;
	static int Orange;
	static int Yellow;
	static int Miku;
	static int Green;

	static const char* bot[6];
	
	static void Render();
	static void TraceLine(vec3d_f center, int index);

	static bool isInScreen(vec2d_f vertex_2d[8]);
	static void Cube(vec3d_f center, float r, int index);
	static void RelativeCube(vec3d_f worldCoords);
	static void String(vec2d_f pos, const char* string, D3DCOLOR color);
	static std::string ToHexString(uintptr_t n);
	static void Line(vec2d_f from, vec2d_f to, D3DCOLOR color);
};

// T: specific typename		A: additional string
template <typename T>
const char* mergeString(T origin, const char* A)
{
	std::stringstream ss;
	ss << std::to_string(origin) << A;
	return ss.str().c_str();
}