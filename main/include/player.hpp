#pragma once

#include "game_object.hpp"
#include "quaternion.hpp"
#include "vector3.hpp"

#include <string>

class Player : public GameObject
{
public:
	REPLICATED('PLAY', Player)
	void Write(OutputStream& stream) override;
	void Read(InputStream& stream) override;
	void Destroy() override;
	void DisplayObject() override;

	void SetName(std::string name);
	void SetPosition(float x, float y, float z); 
	void SetRotation(float w, float x, float y, float z);
		
private:
	Vector3 position;
	Quaternion rotation;
	std::string name = "DefaultName";
};