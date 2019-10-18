#include "linking_context.hpp"


void LinkingContext::Add(GameObject* newGO)
{
	if (objToId.find(newGO) == objToId.end())
	{
		NetworkId newId = idToObj.rbegin->first + 1;
		idToObj.insert({ newId, newGO });
		objToId.insert({ newGO, newId });
	}
	return;
}

void LinkingContext::Add(GameObject* newGO, NetworkId newId)
{
	idToObj.insert({ newId, newGO });
	objToId.insert({ newGO, newId });
	return;
}



void LinkingContext::Remove(GameObject* gameObject)
{
	auto iteratorGO = objToId.find(gameObject);
	if (iteratorGO != objToId.end())
	{
		objToId.erase(iteratorGO);
		idToObj.erase(objToId[gameObject]);
	}
	return;
}


std::optional<NetworkId> LinkingContext::GetId(GameObject* gameObject)
{
	if (objToId.find(gameObject) != objToId.end())
	{
		return objToId[gameObject];
	}
	return {};
}

std::optional<GameObject*> LinkingContext::GetGameObject(NetworkId nId)
{
	if (idToObj.find(nId) != idToObj.end())
	{
		return idToObj[nId];
	}
	return {};
}