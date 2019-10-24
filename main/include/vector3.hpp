#pragma once

#include <cstdint>

class Vector3
{
public:
	float x = 0;
	float y = 0;
	float z = 0;

	uint64_t Pack() const;
	static Vector3 Unpack(uint64_t data);

	static float range;
	static int precision;
};