#pragma once

#include "game_object.hpp"
#include <map>
#include <functional>

using ClassID = uint32_t;

class ClassRegistry
{
public:
	ClassRegistry* GetInstance();
	~ClassRegistry();


	template<class T>
	void Register(T objectClass);

	GameObject* Create(ClassID id);

private:
	ClassRegistry();
	std::map<ClassID, std::function<void()>> classIdToFunction;

	ClassRegistry* instance;

};
