#include "replication_manager.hpp"
#include "linking_context.hpp"
#include "utils.hpp"

void ReplicationManager::Replicate(OutputStream& stream, std::vector<GameObject*> objects)
{
	stream.Write(ReplicationManager::protocolID);

	auto type = to_integral<PacketType>(PacketType::Sync);
	stream.Write(type);

	for (auto gameObject : objects)
	{
		auto objectID = LinkingContext::GetId(gameObject);
		if (!objectID)
		{
			continue;
		}
		stream.Write(*gameObject);

		auto classID = gameObject->ClassID();
		stream.Write(classID);

		gameObject->Write(stream);
	}
	return;
}

void ReplicationManager::Replicate(MemoryStream stream)
{

	return;
}