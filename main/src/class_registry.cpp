#include "class_registry.hpp"


ClassRegistry::ClassRegistry()
{

}

ClassRegistry* ClassRegistry::GetInstance()
{
	if (instance == nullptr)
	{
		return new ClassRegistry();
	}
	else
	{
		return instance;
	}
}

template<class T>
void ClassRegistry::Register(T objectClass)
{
	return;
}

GameObject* ClassRegistry::Create(ClassID id)
{
	return nullptr;
}