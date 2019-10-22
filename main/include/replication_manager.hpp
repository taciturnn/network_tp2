#pragma once

#include "game_object.hpp"
#include "linking_context.hpp"
#include <unordered_set>
#include <vector>


class ReplicationManager
{
public:
	void Replicate(OutputStream& stream, std::vector<GameObject*> objects);
	void Replicate(InputStream& stream);

	void Add(GameObject* gobj);
	void Remove(GameObject* gobj);
	std::vector<GameObject*> GetWorld() const;

	void DisplayWorld();

	enum class PacketType
	{
		Hello = 0x00,
		Sync = 0x01,
		Bye = 0x02
	};

private:
	static const uint32_t protocolID = 0xc0ffee;
	LinkingContext linkingContext;
	std::unordered_set<GameObject*> world;
};