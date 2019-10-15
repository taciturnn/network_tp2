#pragma once

#include "game_object.hpp"

class Ennemy : GameObject
{
public:

	void Write(const OutputStream& stream) override;
	void Read(const InputStream& stream) override;
	void Destroy() override;

private:
	float position_x;
	float position_y;
	float position_z;

	float quaternion_a;
	float quaternion_b;
	float quaternion_c;
	float quaternion_d;

	std::string type;
};