#include "framework.h"

vec2d_f Math::screen;
vec4d_f Math::clipCoords;
vec4d_f Math::NDC;

bool Math::WorldToScreen(vec3d_f pos, vec2d_f& screen, float matrix[16], int windowWidth, int windowHeight)
{

	Math::clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	Math::clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	Math::clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	Math::clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 0.1f)
	{
		return false;
	}

	Math::NDC.x = clipCoords.x / clipCoords.w;
	Math::NDC.y = clipCoords.y / clipCoords.w;
	Math::NDC.z = clipCoords.z / clipCoords.w;

	Math::screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	Math::screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);

	return true;
}



float Math::GetDistance3D(vec3d_f m_pos, vec3d_f en_pos)
{
	return (float)(sqrt(((en_pos.x - m_pos.x) * (en_pos.x - m_pos.x)) + ((en_pos.y - m_pos.y) * (en_pos.y - m_pos.y)) + ((en_pos.z - m_pos.z) * (en_pos.z - m_pos.z))));
}

float Math::GetDistance2D(vec3d_f m_pos, vec3d_f en_pos)
{
	return { (float)(sqrt(
	((en_pos.x - m_pos.x) * (en_pos.x - m_pos.x))
	+ ((en_pos.z - m_pos.z) * (en_pos.z - m_pos.z))
	)) };
}
