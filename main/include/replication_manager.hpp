#pragma once

#include "game_object.hpp"
#include <unordered_set>
#include <vector>

class ReplicationManager
{
public:
	void Replicate(MemoryStream stream, std::vector<GameObject*> objects);
	void Replicate(MemoryStream stream);

private:
	std::unordered_set<GameObject*> world;
};