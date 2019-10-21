#include "server.hpp"
#include "class_registry.hpp"
#include "player.hpp"
#include "ennemy.hpp"

Server::Server(std::string ip, int port, uvw::Loop& srvLoop)
{
	master = ReplicationManager();
	ClassRegistry::GetInstance()->Register(Player());
	ClassRegistry::GetInstance()->Register(Ennemy());

	Player pl1 = Player(); {pl1.SetName("Player_1");}
	Player pl2 = Player(); {pl2.SetName("Player_2");}

	Ennemy en1 = Ennemy(); {en1.SetType("EnnemyType_1");}
	Ennemy en2 = Ennemy(); {en2.SetType("EnnemyType_2");}
	Ennemy en3 = Ennemy(); {en3.SetType("EnnemyType_3");}
	Ennemy en4 = Ennemy(); {en4.SetType("EnnemyType_4");}

	master.world.insert(reinterpret_cast<GameObject*>(&pl1));
	master.world.insert(reinterpret_cast<GameObject*>(&pl2));

	master.world.insert(reinterpret_cast<GameObject*>(&en1));
	master.world.insert(reinterpret_cast<GameObject*>(&en2));
	master.world.insert(reinterpret_cast<GameObject*>(&en3));
	master.world.insert(reinterpret_cast<GameObject*>(&en4));

	std::shared_ptr<uvw::TCPHandle> tcp = srvLoop.resource<uvw::TCPHandle>();
	
	tcp->on<uvw::ListenEvent>([this](const uvw::ListenEvent&, uvw::TCPHandle& srv) {
		std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();
		
		client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent&, uvw::TCPHandle&) { ptr->close(); });
		client->on<uvw::EndEvent>([](const uvw::EndEvent&, uvw::TCPHandle& client) { client.close(); });
		
		srv.accept(*client);
		client->read();
		
		clients.push_back(client);

		// DEBUG
		std::cout << "A new client is connected!" << std::endl;
		SendWorld();
		});

	tcp->bind(ip, port);
	tcp->listen();

	// DEBUG
	std::cout << "The server is listening at " << ip << ":" << std::to_string(port) << std::endl;
}

Server::~Server()
{
	srvLoop->stop();
	srvLoop->close();
}

bool Server::isAlive()
{
	return srvLoop->alive();
}

void Server::SendWorld()
{
	OutputStream stream = OutputStream();
	master.Replicate(stream, std::vector<GameObject*>(master.world.begin(), master.world.end()));
	Send(reinterpret_cast<uint8_t*>(stream.Data().data()), stream.Data().size());
	// Debug 
	std::cout << "The world was sent to the clients!" << std::endl;
}

void Server::Send(uint8_t* packet, size_t size) 
{
	for (auto client : clients)
	{
		auto dataWrite = std::unique_ptr<char[]>(reinterpret_cast<char*>(packet));
		client->write(std::move(dataWrite), size);
	}
	// Debug 
	std::cout << "Data was sent to the clients!" << std::endl;
}