#pragma once

class Math
{
public:

	const double MATH_PI = 3.14159265359f;
	const int HALF_CIRCLE = 180;

	static vec2d_f screen;
	static vec4d_f clipCoords;
	static vec4d_f NDC;

	static bool WorldToScreen(vec3d_f pos, vec2d_f& screen, float matrix[16], int windowWidth, int windowHeight);
	static bool WorldToScreenC(vec3d_f pos, vec2d_f& screen, float matrix[16], int windowWidth, int windowHeight);

	static float GetDistance3D(vec3d_f m_pos, vec3d_f en_pos);
	static float GetDistance2D(vec3d_f m_pos, vec3d_f en_pos);
};
