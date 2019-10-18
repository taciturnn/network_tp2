#include "replication_manager.hpp"
#include "class_registry.hpp"
#include "utils.hpp"

void ReplicationManager::Replicate(OutputStream& stream, std::vector<GameObject*> objects)
{
	stream.Write(ReplicationManager::protocolID);

	auto type = to_integral(PacketType::Sync);
	stream.Write(type);

	for (auto gameObject : objects)
	{
		auto objectID = linkingContext.GetId(gameObject);
		if (!objectID)
		{
			continue;
		}
		stream.Write(*objectID);

		auto classID = gameObject->ClassID();
		stream.Write(classID);

		gameObject->Write(stream);
	}
	return;
}

void ReplicationManager::Replicate(InputStream& stream)
{
	if (stream.Read<uint32_t>() != ReplicationManager::protocolID || stream.Read<PacketType>() != PacketType::Sync)
	{
		stream.Flush();
		return;
	}

	std::unordered_set<GameObject*> realWorld;

	while (stream.Size() > 0)
	{
		NetworkId nId = stream.Read<NetworkId>();
		ClassID cId = stream.Read<ClassID>();
		auto gameObject = linkingContext.GetGameObject(nId);
		GameObject* go;
		if (!gameObject)
		{
			go = ClassRegistry::GetInstance()->Create(cId);
		}
		else
		{
			go = gameObject.value();
		}

		go->Read(stream);
		realWorld.insert(go);
	}

	for (auto gameObject : world)
	{
		if (realWorld.find(gameObject) == realWorld.end())
		{
			world.erase(gameObject);
		}
	}

	return;
}