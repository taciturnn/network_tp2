#include "quaternion.hpp"

#include <algorithm>

uint32_t Quaternion::Pack() const
{
	float maxValue = w;
	uint8_t caseToIgnore = 0;
	
	if (x > maxValue)
	{
		maxValue = x;
		caseToIgnore = 1;
	}
	if (y > maxValue)
	{
		maxValue = y;
		caseToIgnore = 2;
	}
	if (z > maxValue)
	{
		maxValue = z;
		caseToIgnore = 3;
	}

	uint32_t result = caseToIgnore;
	uint8_t offset = 2;
	if (caseToIgnore != 0)
	{
		result += (static_cast<uint32_t>((((w + 0.707f) * 1000) * 1024) / 1414) << offset);
		offset += 10;
	}
	if (caseToIgnore != 1)
	{
		result += (static_cast<uint32_t>((((x + 0.707f) * 1000) * 1024) / 1414) << offset);
		offset += 10;
	}
	if (caseToIgnore != 2)
	{
		result += (static_cast<uint32_t>((((y + 0.707f) * 1000) * 1024) / 1414) << offset);
		offset += 10;
	}
	if (caseToIgnore != 3)
	{
		result += (static_cast<uint32_t>((((z + 0.707f) * 1000) * 1024) / 1414) << offset);
	}

	return result;
}

Quaternion Quaternion::Unpack(uint32_t data)
{
	Quaternion result;

	uint8_t caseToIgnore = 0x3 & data;

	uint8_t offset = 2;
	float sumOfSqr = 0;
	if (caseToIgnore != 0)
	{
		result.w = (static_cast<float>(((0x3FF & (data >> offset)) * 1414) / 1024) / 1000.f) - 0.707f;
		sumOfSqr += result.w * result.w;
		offset += 10;
	}
	if (caseToIgnore != 1)
	{
		result.x = (static_cast<float>(((0x3FF & (data >> offset)) * 1414) / 1024) / 1000.f) - 0.707f;
		sumOfSqr += result.x * result.x;
		offset += 10;
	}
	if (caseToIgnore != 2)
	{
		result.y = (static_cast<float>(((0x3FF & (data >> offset)) * 1414) / 1024) / 1000.f) - 0.707f;
		sumOfSqr += result.y * result.y;
		offset += 10;
	}
	if (caseToIgnore != 3)
	{
		result.z = (static_cast<float>(((0x3FF & (data >> offset)) * 1414) / 1024) / 1000.f) - 0.707f;
		sumOfSqr += result.z * result.z;
	}

	if (caseToIgnore == 0) {
		result.w = sqrtf(1.0f - sumOfSqr);
	}
	if (caseToIgnore == 1) {
		result.x = sqrtf(1.0f - sumOfSqr);
	}
	if (caseToIgnore == 2) {
		result.y = sqrtf(1.0f - sumOfSqr);
	}
	if (caseToIgnore == 3) {
		result.z = sqrtf(1.0f - sumOfSqr);
	}

	return result;
}