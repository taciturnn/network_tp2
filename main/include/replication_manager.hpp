#pragma once

#include "game_object.hpp"
#include <unordered_set>
#include <vector>

class ReplicationManager
{
public:
	void Replicate(OutputStream& stream, std::vector<GameObject*> objects);
	void Replicate(InputStream& stream);

private:
	std::unordered_set<GameObject*> world;
	LinkingContext linkingContext;
};