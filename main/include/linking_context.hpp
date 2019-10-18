#include "game_object.hpp"
#pragma once

#include <map>
#include <optional>

using NetworkId = uint32_t;

class LinkingContext
{
public:
	void Add(GameObject*);
	void Add(GameObject*, NetworkId);
	void Remove(GameObject*);

	std::optional<NetworkId> GetId(GameObject*);
	std::optional<GameObject *> GetGameObject(NetworkId);

private:
	std::map<NetworkId, GameObject*> idToObj;
	std::map<GameObject*, NetworkId> objToId;
};