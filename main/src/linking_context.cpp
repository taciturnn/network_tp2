#include "linking_context.hpp"


void LinkingContext::Add(GameObject*)
{
	return;
}


void LinkingContext::Remove(GameObject*)
{
	return;
}


std::optional<NetworkId> LinkingContext::GetId(GameObject*)
{
	return {};
}

std::optional<GameObject*> LinkingContext::GetGameObject(NetworkId)
{
	return {};
}