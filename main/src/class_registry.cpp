#include "class_registry.hpp"
#include "streams.hpp"

ClassRegistry* ClassRegistry::GetInstance()
{
	static ClassRegistry instance;
	return &instance;
}

GameObject* ClassRegistry::Create(ClassID id)
{
	auto index = classIdToFunction.find(id);
	assert(index != classIdToFunction.end()); // crash if type is not in map
	return (index->second)();
}