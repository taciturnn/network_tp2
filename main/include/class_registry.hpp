#pragma once

#include "game_object.hpp"
#include <map>
#include <functional>

using ClassID = uint32_t;

class ClassRegistry
{
public:
	static ClassRegistry* GetInstance();

	template<class T>
	void Register(T classObject)
	{
		classIdToFunction.insert(std::make_pair(classObject.ClassID(), classObject.CreateInstance));
	}

	GameObject* Create(ClassID id);

private:
	ClassRegistry() = default;
	~ClassRegistry() = default;

	std::map<ClassID, std::function<GameObject*()>> classIdToFunction;
};
