#include "player.hpp"
#include "streams.hpp"
#include <iostream>
#include <string>
#include <math.h>

void Player::SetName(std::string name)
{
	this->name = name;
}

void Player::SetPosition(float x, float y, float z)
{
	// NO VALIDATION THAT THE POSITION IS VALID (ASSUMED TO BE -500->500)
	position.x = x;
	position.y = y;
	position.z = z;
}

void Player::SetRotation(float w, float x, float y, float z)
{
	// NO VALIDATION THAT THE QUATERNION IS VALID (ASSUMED TO BE -0.707->0.707)
	rotation.w = w;
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}


void Player::Write(OutputStream& stream)
{
	// Send position (vector3)
	uint64_t posToSend = position.Pack();
	stream.Write(posToSend);

	// Send rotation (quaternion)
	uint32_t quatToSend = rotation.Pack();
	stream.Write(quatToSend);

	// Send the name
	stream.WriteStr(name);

};


void Player::Read(InputStream& stream)
{
	// Receive the new position
	uint64_t receivedPos = stream.Read<uint64_t>();
	position = Vector3::Unpack(receivedPos);

	//Receive the new quaternion
	uint32_t receivedQuat = stream.Read<uint32_t>();
	rotation = Quaternion::Unpack(receivedQuat);

	// Read the name
	name = stream.ReadStr();

};

void Player::Destroy()
{
	return;
}

void Player::DisplayObject()
{
	std::cout << "    ============================================" << std::endl;
	std::cout << "    ==                 PLAYER                 ==" << std::endl;
	std::cout << "    ============================================" << std::endl;
	std::cout << "    name : " << name << std::endl;
	std::cout << "    position x : " << std::to_string(position.x) << std::endl;
	std::cout << "    position y : " << std::to_string(position.y) << std::endl;
	std::cout << "    position z : " << std::to_string(position.z) << std::endl;
	std::cout << "    quaternion a : " << std::to_string(rotation.w) << std::endl;
	std::cout << "    quaternion b : " << std::to_string(rotation.x) << std::endl;
	std::cout << "    quaternion c : " << std::to_string(rotation.y) << std::endl;
	std::cout << "    quaternion d : " << std::to_string(rotation.z) << std::endl;
	std::cout << "    ============================================" << std::endl;
}