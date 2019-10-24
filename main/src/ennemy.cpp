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
	position.x = x;
	position.y = y;
	position.z = z;
}

void Ennemy::SetRotation(float w, float x, float y, float z)
{
	// NO VALIDATION THAT THE QUATERNION IS VALID (ASSUMED TO BE -0.707->0.707)
	rotation.w = w;
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

void Ennemy::Write(OutputStream& stream)
{
	// Send position (vector3)
	uint64_t posToSend = position.Pack();
	stream.Write(posToSend);

	// Send rotation (quaternion)
	uint32_t quatToSend = rotation.Pack();
	stream.Write(quatToSend);

	// Send type
	stream.WriteStr(type);
}

void Ennemy::Read(InputStream& stream)
{
	// Receive the new position
	uint64_t receivedPos = stream.Read<uint64_t>();
	position = Vector3::Unpack(receivedPos);

	//Receive the new quaternion
	uint32_t receivedQuat = stream.Read<uint32_t>();
	rotation = Quaternion::Unpack(receivedQuat);

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
	std::cout << "    position x : " << std::to_string(position.x) << std::endl;
	std::cout << "    position y : " << std::to_string(position.y) << std::endl;
	std::cout << "    position z : " << std::to_string(position.z) << std::endl;
	std::cout << "    quaternion w : " << std::to_string(rotation.w) << std::endl;
	std::cout << "    quaternion x : " << std::to_string(rotation.x) << std::endl;
	std::cout << "    quaternion y : " << std::to_string(rotation.y) << std::endl;
	std::cout << "    quaternion z : " << std::to_string(rotation.z) << std::endl;
	std::cout << "    ============================================" << std::endl;
}