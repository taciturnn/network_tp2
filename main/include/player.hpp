#pragma once

#include "game_object.hpp"
#include <string>

class Player : public GameObject
{
public:
	REPLICATED('PLAY', Player)
	void Write(OutputStream& stream) override;
	void Read(InputStream& stream) override;
	void Destroy() override;

	void SetName(std::string name);
	void SetPosition(float x, float y, float z);
	void SetRotation(float a, float b, float c, float d);
		
private:
	float position_x = 0.f;
	float position_y = 0.f;
	float position_z = 0.f;

	float quaternion_a =  0.f;
	float quaternion_b =  0.f;
	float quaternion_c =  0.f;
	float quaternion_d =  0.f;

	std::string name = "DefaultName";
};