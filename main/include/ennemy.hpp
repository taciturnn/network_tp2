#pragma once

#include "game_object.hpp"
#include "quaternion.hpp"
#include "vector3.hpp"

class Ennemy : public GameObject
{
public:
	REPLICATED('ENMY', Ennemy)

	void Write(OutputStream& stream) override;
	void Read(InputStream& stream) override;
	void Destroy() override;
	void DisplayObject() override;

	void SetType(std::string name);
	void SetPosition(float x, float y, float z);
	void SetRotation(float w, float x, float y, float z);

private:
	Vector3 position;
	Quaternion rotation;
	std::string type = "DefaultType";
};