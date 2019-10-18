#include "player.hpp"
#include "streams.hpp"


void Player::Write(OutputStream& stream)
{

	// Send position
	uint64_t t_x = static_cast<uint64_t>((position_x + 500.) * 1000);
	uint64_t t_y = static_cast<uint64_t>((position_y + 500.) * 1000);
	uint64_t t_z = static_cast<uint64_t>((position_z + 500.) * 1000);

	uint64_t posToSend = t_x << 40 + t_y << 20 + t_z;

	stream.Write<uint64_t>(posToSend);

	// Send quaternion
	float valueToIgnore = -1;
	uint8_t caseToIgnore = 0;
	if (quaternion_a >= valueToIgnore) valueToIgnore = quaternion_a; caseToIgnore = 0;
	if (quaternion_b >= valueToIgnore) valueToIgnore = quaternion_b; caseToIgnore = 1;
	if (quaternion_c >= valueToIgnore) valueToIgnore = quaternion_c; caseToIgnore = 2;
	if (quaternion_d >= valueToIgnore) valueToIgnore = quaternion_d; caseToIgnore = 3;

	uint32_t quatToSend = caseToIgnore;
	uint8_t offset = 2;
	if (caseToIgnore != 0)
	{
		quatToSend += (static_cast<uint32_t>((((quaternion_a + 0.707) * 1000) / 1047) * 1024) << offset);
		offset += 10;
	}
	if (caseToIgnore != 1)
	{
		quatToSend += (static_cast<uint32_t>((((quaternion_b + 0.707) * 1000) / 1047) * 1024) << offset);
		offset += 10;
	}
	if (caseToIgnore != 2)
	{
		quatToSend += (static_cast<uint32_t>((((quaternion_c + 0.707) * 1000) / 1047) * 1024) << offset);
		offset += 10;
	}
	if (caseToIgnore != 3)
	{
		quatToSend += (static_cast<uint32_t>((((quaternion_d + 0.707) * 1000) / 1047) * 1024) << offset);
	}

	stream.Write<uint32_t>(quatToSend);

	// Send the name
	stream.WriteStr(name);

};


void Player::Read(InputStream& stream)
{

	// Receive the new position
	uint64_t receivedPos = stream.Read<uint64_t>();
	uint64_t t_z = 0x00000000000FFFFF & receivedPos;
	uint64_t t_y = 0x00000000000FFFFF & receivedPos >> 20;
	uint64_t t_x = 0xFFFFF & receivedPos >> 40;

	position_x = (t_x / 1000) - 500;
	position_y = (t_y / 1000) - 500;
	position_z = (t_z / 1000) - 500;

	//Receive the new quaternion
	uint32_t receivedQuat = stream.Read<uint32_t>();
	uint8_t caseToIgnore = 0x2 & receivedQuat;

	uint8_t offset = 2;
	uint32_t sumOfSqr = 0;
	if (caseToIgnore != 0)
	{
		quaternion_a = (static_cast<float>((0x3FF & receivedQuat >> offset) * 1047) / 1000) - 0.707;
		sumOfSqr += quaternion_a * quaternion_a;
		offset += 10;
	}
	if (caseToIgnore != 1)
	{
		quaternion_a = (static_cast<float>((0x3FF & receivedQuat >> offset) * 1047) / 1000) - 0.707;
		sumOfSqr += quaternion_b * quaternion_b;
		offset += 10;
	}
	if (caseToIgnore != 2)
	{
		quaternion_a = (static_cast<float>((0x3FF & receivedQuat >> offset) * 1047) / 1000) - 0.707;
		sumOfSqr += quaternion_c * quaternion_c;
		offset += 10;
	}
	if (caseToIgnore != 3)
	{
		quaternion_a = (static_cast<float>((0x3FF & receivedQuat >> offset) * 1047) / 1000) - 0.707;
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

	// Read the name
	name = stream.ReadStr();

};

void Player::Destroy()
{
	return;
}