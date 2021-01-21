#pragma once


#pragma pack(push, 1)
typedef struct
{
	float x, y;
} vec2d_f;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
	float x, y, z;
} vec3d_f;
#pragma pack(pop)

typedef struct
{
	float x, y, z, w;
} vec4d_f;
