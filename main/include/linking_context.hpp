#include "game_object.hpp"
#pragma once

#include <map>
#include <optional>

using NetworkId = uint32_t;

class LinkingContext
{
public:
	void Add(GameObject*);
	void Remove(GameObject*);

	std::optional<NetworkId> GetId(GameObject*);
	std::optional<GameObject *> GetGameObject(NetworkId);

	//Ajoutez une méthode permettant d’ajouter un pointeur sur un GameObject et un NetworkID au contexte

private:
	std::map<NetworkId, GameObject*> idToObj;
	std::map<GameObject*, NetworkId> objToId;
};