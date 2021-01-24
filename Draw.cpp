#include "framework.h"

#define M_PI 3.141f

int Draw::Red =		D3DCOLOR_ARGB(255, 255, 000, 000);
int Draw::White =	D3DCOLOR_ARGB(255, 255, 255, 255);
int Draw::Orange =	D3DCOLOR_ARGB(255, 255, 125, 000);
int Draw::Yellow =	D3DCOLOR_ARGB(255, 255, 255, 000);
int Draw::Miku =	D3DCOLOR_ARGB(255, 000, 255, 255);
int Draw::Green =	D3DCOLOR_ARGB(255, 000, 255, 000);

IDirect3D9Ex*			d3dObject;
IDirect3DDevice9Ex*		d3dDevice;
D3DPRESENT_PARAMETERS	d3dparams;
ID3DXFont*				d3dFont;
ID3DXFont*				d3despFont;
ID3DXFont*				d3dFontWarning;
ID3DXLine*				d3dLine;

const char* Draw::bot[6] = { "Alfa" , "Bravo", "Charlie", "Delta", "Echo", "Foxtrot" };

void Draw::Initial(HWND overlayHWND) {
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &d3dObject))) {
		exit(1);
	}
	ZeroMemory(&d3dparams, sizeof(d3dparams));

	d3dparams.Windowed =				true;
	d3dparams.BackBufferWidth =			Game::width;
	d3dparams.BackBufferHeight =		Game::height;
	d3dparams.BackBufferFormat =		D3DFMT_A8R8G8B8;

	d3dparams.SwapEffect =				D3DSWAPEFFECT_DISCARD;
	d3dparams.hDeviceWindow =			overlayHWND;
	d3dparams.MultiSampleQuality =		D3DMULTISAMPLE_NONE;
	d3dparams.EnableAutoDepthStencil =	true;
	d3dparams.AutoDepthStencilFormat =	D3DFMT_D16;

	HRESULT res = d3dObject->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, overlayHWND, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dparams, 0, &d3dDevice);
	if (FAILED(res))
		exit(1);

	D3DXCreateFont(d3dDevice, 30, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Comic Sans", &d3dFont);
	//D3DXCreateFont(d3dDevice, 20, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &d3dFont);
	D3DXCreateFont(d3dDevice, 13, 0, 0, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Arial", &d3despFont);

	// VERY IMPORTANT , IF MISSING, NULL PTR EXCEPTION WILL HAPPEN WHILE DRAW LINES AND RECTANGLES   !!!
	if (!d3dLine)
		D3DXCreateLine(d3dDevice, &d3dLine);
}

void Draw::Render()
{
	if (d3dDevice == nullptr)
		return;
	d3dDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
	d3dDevice->BeginScene();
	if (Game::winHWND == GetForegroundWindow())
	{
		// Gets self info
		//Self::GetOpCoords();
		Self::GetWorldCoords();
		Draw::RelativeCube(Self::worldCoords);
	}
	d3dDevice->EndScene();
	d3dDevice->PresentEx(0, 0, 0, 0, 0);

	return;
}

void Draw::TraceLine(vec3d_f center, int index)
{
	vec2d_f from = { Game::width / 2, Game::height };
	if (Math::WorldToScreenC(center, Math::screen, Self::viewMatrix, Game::width, Game::height))
	{
		Draw::Line(from, Math::screen, Yellow);
		Draw::String(Math::screen, bot[index], Red);
	}
}

bool Draw::isInScreen(vec2d_f vertex_2d[8])
{
	float min_x = 1e6 + 7, max_x = -1e6 - 7;
	float min_y = 1e6 + 7, max_y = -1e6 - 7;

	for (int i = 0; i < 8; i++) {
		float x = vertex_2d[i].x, y = vertex_2d[i].y;
		if (x > max_x) max_x = x;
		if (x < min_x) min_x = x;
		if (y > max_y) max_y = y;
		if (y < min_y) min_y = y;
	}
	return min_x > Game::right || max_x < Game:: left || min_y > Game::top || max_y < Game::bottom;
}

void Draw::Cube(vec3d_f center, float r, int index)
{
	float x = center.x, y = center.y, z = center.z;
	// generates vertex
	vec3d_f vertex[8] = {};
	vertex[0] = { x - r, y - r, z + r };
	vertex[1] = { x + r, y - r, z + r };
	vertex[2] = { x + r, y + r, z + r };
	vertex[3] = { x - r, y + r, z + r };

	vertex[4] = { x - r, y - r, z - r };
	vertex[5] = { x + r, y - r, z - r };
	vertex[6] = { x + r, y + r, z - r };
	vertex[7] = { x - r, y + r, z - r };
	// draws
	Self::GetViewMatrix();
	vec2d_f vertex_2d[8] = {};
	for (int i = 0; i < 8; i++) {
		if (Math::WorldToScreenC(vertex[i], Math::screen, Self::viewMatrix, Game::width, Game::height)) {
			vertex_2d[i] = Math::screen;
		}
	}
	// draws only if cube in screen
	if (!Draw::isInScreen(vertex_2d)) return;
	Draw::Line(vertex_2d[0], vertex_2d[1], Yellow);
	Draw::Line(vertex_2d[1], vertex_2d[2], Yellow);
	Draw::Line(vertex_2d[2], vertex_2d[3], Yellow);
	Draw::Line(vertex_2d[3], vertex_2d[0], Yellow);

	Draw::Line(vertex_2d[4], vertex_2d[5], Yellow);
	Draw::Line(vertex_2d[5], vertex_2d[6], Yellow);
	Draw::Line(vertex_2d[6], vertex_2d[7], Yellow);
	Draw::Line(vertex_2d[7], vertex_2d[4], Yellow);

	Draw::Line(vertex_2d[0], vertex_2d[4], Yellow);
	Draw::Line(vertex_2d[1], vertex_2d[5], Yellow);
	Draw::Line(vertex_2d[2], vertex_2d[6], Yellow);
	Draw::Line(vertex_2d[3], vertex_2d[7], Yellow);

	Draw::TraceLine(center, index);
}



void Draw::RelativeCube(vec3d_f worldCoords)
{
	float x = worldCoords.x, y = worldCoords.y, z = worldCoords.z;
	float re = 12.f;
	// front, behind, left, right
	Draw::Cube({ x, y + re, z }, 1, 0);
	Draw::Cube({ x, y - re, z }, 1, 1);
	Draw::Cube({ x - re, y, z }, 1, 2);
	Draw::Cube({ x + re, y, z }, 1, 3);
	// above, below
	Draw::Cube({ x, y, z + re}, 1, 4);
	Draw::Cube({ x, y, z - re}, 1, 5);
}


void Draw::Line(vec2d_f from, vec2d_f to, D3DCOLOR color)
{
	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(from.x, from.y);
	Line[1] = D3DXVECTOR2(to.x, to.y);
	d3dLine->SetWidth(2);
	d3dLine->Draw(Line, 2, color);
}

void Draw::String(vec2d_f pos, const char* string, D3DCOLOR color)
{
	RECT Position;
	Position.left = pos.x + 1;
	Position.top = pos.y + 1;
	d3dFont->DrawTextA(0, string, strlen(string), &Position, DT_NOCLIP, color);
}

// const char* cc = string_value.c_str();
std::string Draw::ToHexString(uintptr_t n)
{
	std::string res = "";
	uintptr_t stk[100] = {};
	int tt = 0;
	for (; n; n /= 16) {
		stk[++tt] = n % 16;				// push
	}
	for (; tt; tt--) {
		switch (stk[tt]) {				// pop
		case 10:res += "A"; break;
		case 11:res += "B"; break;
		case 12:res += "C"; break;
		case 13:res += "D"; break;
		case 14:res += "E"; break;
		case 15:res += "F"; break;
		default:res += std::to_string(stk[tt]); break;
		}
	}
	return res;
}





