#include "ennemy.hpp"
#include "streams.hpp"

void Ennemy::Write(OutputStream& stream)
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
	uint8_t nextMove = 2;
	if (caseToIgnore != 0)
	{
		quatToSend += (static_cast<uint32_t>((((quaternion_a + 0.707) * 1000) / 1047) * 1024) << nextMove);
		nextMove += 10;
	}
	if (caseToIgnore != 1)
	{
		quatToSend += (static_cast<uint32_t>((((quaternion_b + 0.707) * 1000) / 1047) * 1024) << nextMove);
		nextMove += 10;
	}
	if (caseToIgnore != 2)
	{
		quatToSend += (static_cast<uint32_t>((((quaternion_c + 0.707) * 1000) / 1047) * 1024) << nextMove);
		nextMove += 10;
	}
	if (caseToIgnore != 3)
	{
		quatToSend += (static_cast<uint32_t>((((quaternion_d + 0.707) * 1000) / 1047) * 1024) << nextMove);
	}

	stream.Write<uint32_t>(quatToSend);

	//Send type
	return;
}

void Ennemy::Read(InputStream& stream)
{
	return;
}

void Ennemy::Destroy()
{
	return;
}
