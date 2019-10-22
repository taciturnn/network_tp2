#include "linking_context.hpp"

NetworkId LinkingContext::Add(GameObject* newGO)
{
	auto iteratorGO = objToId.find(newGO);
	if (iteratorGO == objToId.end())
	{
		NetworkId newId = idToObj.empty() ? 0 : (idToObj.rbegin()->first) + 1; //get highest key + 1
		idToObj.insert({ newId, newGO });
		objToId.insert({ newGO, newId });
		return newId;
	}
	else return objToId[newGO];
	
}

void LinkingContext::Add(GameObject* newGO, NetworkId newId)
{
	if (idToObj.find(newId) != idToObj.end())
	{
		idToObj.insert({ newId, newGO });
		objToId.insert({ newGO, newId });
	}
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