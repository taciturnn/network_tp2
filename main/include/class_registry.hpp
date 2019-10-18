#pragma once

#include "game_object.hpp"
#include <map>
#include <functional>

using ClassID = uint32_t;

class ClassRegistry
{
public:
	ClassRegistry* GetInstance();
	~ClassRegistry() = default;

	template<class T>
	void Register(T objectClass)
	{
		classIdToFunction.insert(std::make_pair(T.ClassID(), T.CreateInstance));
	}

	GameObject* Create(ClassID id);

private:
	ClassRegistry() = default;

	std::map<ClassID, std::function<GameObject*()>> classIdToFunction;

	ClassRegistry* instance;

};
