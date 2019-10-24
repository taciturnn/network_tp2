#pragma once

#include <cstdint>

class Quaternion
{
public:
	float w = 1;
	float x = 0;
	float y = 0;
	float z = 0;

	uint32_t Pack() const;
	static Quaternion Unpack(uint32_t data);
};