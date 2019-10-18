#include "replication_manager.hpp"
#include "linking_context.hpp"
#include "class_registry.hpp"


void ReplicationManager::Replicate(OutputStream& stream, std::vector<GameObject*> objects)
{
	/*
	stream.Write(ReplicationManager::protocolID);

	auto type = to_intergral(PacketType::Sync);
	stream.Write(type);
	*/

	for (auto gameObject : objects)
	{
		auto objectID = linkingContext.GetId(gameObject);
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

void ReplicationManager::Replicate(InputStream& stream)
{
	//TODO : read protocol and object ID

	std::unordered_set<GameObject*> realWorld;


	while (stream.Size() > 0)
	{
		NetworkId nId = stream.Read<NetworkId>();
		ClassID cId = stream.Read<ClassID>();
		auto gameObject = linkingContext.GetGameObject(nId);
		if (!gameObject)
		{
			ClassRegistry::GetInstance()->Create(cId);
		} 

		gameObject->Read(stream);
		realWorld.insert(gameObject);
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