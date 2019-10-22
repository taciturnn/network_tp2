#include "replication_manager.hpp"
#include "class_registry.hpp"
#include "utils.hpp"
#include <iostream>

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
			std::cout << "Error: object not found in linking context" << std::endl;
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


void ReplicationManager::Add(GameObject* gobj)
{
	linkingContext.Add(gobj);
	world.insert(gobj);
}


void ReplicationManager::Remove(GameObject* gobj)
{
	linkingContext.Remove(gobj);
	world.erase(gobj);
}

std::vector<GameObject*> ReplicationManager::GetWorld() const
{
	return std::vector<GameObject*>(world.begin(), world.end());
}

void ReplicationManager::DisplayWorld()
{
	std::cout << "==========================================================================" << std::endl;
	std::cout << "Display world" << std::endl;
	std::cout << "==========================================================================" << std::endl;
	for (auto object : world)
	{
		std::cout << object->mClassID << " : " << linkingContext.GetId(object).value() << std::endl;
	}
	std::cout << "==========================================================================" << std::endl;
}