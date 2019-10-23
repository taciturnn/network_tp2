#include "ennemy.hpp"
#include "streams.hpp"
#include <iostream>
#include <string>
#include <math.h>

void Ennemy::SetType(std::string name)
{
	this->type= name;
}

void Ennemy::SetPosition(float x, float y, float z)
{
	// NO VALIDATION THAT THE POSITION IS VALID (ASSUMED TO BE -500->500)
	position_x = x;
	position_y = y;
	position_z = z;
}

void Ennemy::SetRotation(float a, float b, float c, float d)
{
	// NO VALIDATION THAT THE QUATERNION IS VALID (ASSUMED TO BE -0.707->0.707)
	quaternion_a = a;
	quaternion_b = b;
	quaternion_c = c;
	quaternion_d = d;
}

void Ennemy::Write(OutputStream& stream)
{

	// Send position
	uint64_t t_x = static_cast<uint64_t>((position_x + 500.) * 1000);
	uint64_t t_y = static_cast<uint64_t>((position_y + 500.) * 1000);
	uint64_t t_z = static_cast<uint64_t>((position_z + 500.) * 1000);

	uint64_t posToSend = (t_x << 40) + (t_y << 20) + t_z;

	stream.Write(posToSend);
	
	
	// Send quaternion
	float valueToIgnore = -1;
	uint8_t caseToIgnore = 0;
	if (quaternion_a >= valueToIgnore) { valueToIgnore = quaternion_a; caseToIgnore = 0; }
	if (quaternion_b >= valueToIgnore) { valueToIgnore = quaternion_b; caseToIgnore = 1; }
	if (quaternion_c >= valueToIgnore) { valueToIgnore = quaternion_c; caseToIgnore = 2; }
	if (quaternion_d >= valueToIgnore) { valueToIgnore = quaternion_d; caseToIgnore = 3; }

	uint32_t quatToSend = caseToIgnore;
	uint8_t offset = 2;
	if (caseToIgnore != 0)
	{
		quatToSend += (static_cast<uint32_t>((((quaternion_a + 0.707) * 1000) * 1024) / 1414)  << offset);
		offset += 10;
	}
	if (caseToIgnore != 1)
	{
		quatToSend += (static_cast<uint32_t>((((quaternion_b + 0.707) * 1000) * 1024) / 1414) << offset);
		offset += 10;
	}
	if (caseToIgnore != 2)
	{
		quatToSend += (static_cast<uint32_t>((((quaternion_c + 0.707) * 1000) * 1024) / 1414) << offset);
		offset += 10;
	}
	if (caseToIgnore != 3)
	{
		quatToSend += (static_cast<uint32_t>((((quaternion_d + 0.707) * 1000) * 1024) / 1414) << offset);
	}

	stream.Write(quatToSend);

	// Send the type
	stream.WriteStr(type);
}

void Ennemy::Read(InputStream& stream)
{

	// Receive the new position
	uint64_t receivedPos = stream.Read<uint64_t>();
	uint64_t t_z = 0xFFFFF & receivedPos;
	uint64_t t_y = 0xFFFFF & (receivedPos >> 20);
	uint64_t t_x = 0xFFFFF & (receivedPos >> 40);

	position_x = (t_x / 1000.f) - 500;
	position_y = (t_y / 1000.f) - 500;
	position_z = (t_z / 1000.f) - 500;

	//Receive the new quaternion
	uint32_t receivedQuat = stream.Read<uint32_t>();
	uint8_t caseToIgnore = 0x3 & receivedQuat;

	uint8_t offset = 2;
	float sumOfSqr = 0;
	if (caseToIgnore != 0)
	{
		quaternion_a = (static_cast<float>(((0x3FF & (receivedQuat >> offset)) * 1414) / 1024) / 1000.f) - 0.707f;
		sumOfSqr += quaternion_a * quaternion_a;
		offset += 10;
	}
	if (caseToIgnore != 1)
	{
		quaternion_b = (static_cast<float>(((0x3FF & (receivedQuat >> offset)) * 1414) / 1024) / 1000.f) - 0.707f;
		sumOfSqr += quaternion_b * quaternion_b;
		offset += 10;
	}
	if (caseToIgnore != 2)
	{
		quaternion_c = (static_cast<float>(((0x3FF & (receivedQuat >> offset)) * 1414) / 1024) / 1000.f) - 0.707f;
		sumOfSqr += quaternion_c * quaternion_c;
		offset += 10;
	}
	if (caseToIgnore != 3)
	{
		quaternion_d = (static_cast<float>(((0x3FF & (receivedQuat >> offset)) * 1414) / 1024) / 1000.f) - 0.707f;
		sumOfSqr += quaternion_d * quaternion_d;
	}

	if (caseToIgnore == 0) {
		quaternion_a = sqrtf(1.0f - sumOfSqr);
	}
	if (caseToIgnore == 1) {
		quaternion_b = sqrtf(1.0f - sumOfSqr);
	}
	if (caseToIgnore == 2) {
		quaternion_c = sqrtf(1.0f - sumOfSqr);
	}
	if (caseToIgnore == 3) {
		quaternion_d = sqrtf(1.0f - sumOfSqr);
	}

	// Read the type
	type = stream.ReadStr();
}

void Ennemy::Destroy()
{
	return;
}

void Ennemy::DisplayObject()
{
	std::cout << "    ============================================" << std::endl;
	std::cout << "    ==                 ENNEMY                 ==" << std::endl;
	std::cout << "    ============================================" << std::endl;
	std::cout << "    type : " << type << std::endl;
	std::cout << "    position x : " << std::to_string(position_x) << std::endl;
	std::cout << "    position y : " << std::to_string(position_y) << std::endl;
	std::cout << "    position z : " << std::to_string(position_z) << std::endl;
	std::cout << "    quaternion a : " << std::to_string(quaternion_a) << std::endl;
	std::cout << "    quaternion b : " << std::to_string(quaternion_b) << std::endl;
	std::cout << "    quaternion c : " << std::to_string(quaternion_c) << std::endl;
	std::cout << "    quaternion d : " << std::to_string(quaternion_d) << std::endl;
	std::cout << "    ============================================" << std::endl;
}