#include "vector3.hpp"

float Vector3::range = 500;
int Vector3::precision = 1000;

uint64_t Vector3::Pack() const
{
	uint64_t t_x = static_cast<uint64_t>((x + range) * precision);
	uint64_t t_y = static_cast<uint64_t>((y + range) * precision);
	uint64_t t_z = static_cast<uint64_t>((z + range) * precision);

	return (t_x << 40) + (t_y << 20) + t_z;
}

Vector3 Vector3::Unpack(uint64_t data)
{
	uint64_t t_z = 0xFFFFF & data;
	uint64_t t_y = 0xFFFFF & (data >> 20);
	uint64_t t_x = 0xFFFFF & (data >> 40);

	Vector3 result;
	result.x = (t_x / static_cast<float>(precision)) - range;
	result.y = (t_y / static_cast<float>(precision)) - range;
	result.z = (t_z / static_cast<float>(precision)) - range;

	return result;
}