#include "server.hpp"
#include "class_registry.hpp"
#include "player.hpp"
#include "ennemy.hpp"

Server::Server(std::string ip, int port, std::shared_ptr<uvw::Loop> srvLoop)
{
	master = ReplicationManager();
	ClassRegistry::GetInstance()->Register(Player());
	ClassRegistry::GetInstance()->Register(Ennemy());

	auto pl1 = std::make_unique<Player>(); pl1->SetName("Player_1"); master.Add(pl1.get()); myPlayers.push_back(std::move(pl1));
	auto pl2 = std::make_unique<Player>(); pl2->SetName("Player_2"); master.Add(pl2.get()); myPlayers.push_back(std::move(pl2));

	auto en1 = std::make_unique<Ennemy>(); en1->SetType("EnnemyType_1"); en1->SetRotation(0.5,0.5,0.5,0.5); master.Add(en1.get()); myEnnemies.push_back(std::move(en1));
	auto en2 = std::make_unique<Ennemy>(); en2->SetType("EnnemyType_2"); en2->SetRotation(0.227f,0.159f,0.679f,0.679f); master.Add(en2.get()); myEnnemies.push_back(std::move(en2));
	auto en3 = std::make_unique<Ennemy>(); en3->SetType("EnnemyType_3"); en3->SetRotation(0.499f,0.621f,0.621f,-0.162f); master.Add(en3.get()); myEnnemies.push_back(std::move(en3));
	auto en4 = std::make_unique<Ennemy>(); en4->SetType("EnnemyType_4"); en4->SetRotation(0.208f,0.662f,-0.699f,-0.173f); master.Add(en4.get()); myEnnemies.push_back(std::move(en4));

	auto tcp = srvLoop->resource<uvw::TCPHandle>();
	
	tcp->on<uvw::ListenEvent>([this](const uvw::ListenEvent&, uvw::TCPHandle& srv) {
		std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();
		
		client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent&, uvw::TCPHandle&) {
			std::cout << "Close Event launched!" << std::endl;
			ptr->close(); 
		});

		client->on<uvw::EndEvent>([](const uvw::EndEvent&, uvw::TCPHandle& client) { 
			std::cout << "End event for client!" << std::endl;
			client.close(); 
		});

		client->on<uvw::ErrorEvent>([](const uvw::ErrorEvent& e, uvw::TCPHandle&) { std::cout << e.name() << ": " << e.what() << std::endl; });

		client->on<uvw::ExitEvent>([](const uvw::ExitEvent&, uvw::TCPHandle& client) {
			std::cout << "Exit event for client!" << std::endl;
		});

		srv.accept(*client);
		
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

void Server::SendWorld()
{
	OutputStream stream;
	master.Replicate(stream, master.GetWorld());
	std::cout << "Sending world >>>>> " << std::endl;
	master.DisplayWorld();
	Send(reinterpret_cast<uint8_t*>(stream.Data().data()), static_cast<size_t>(stream.Data().size_bytes()));
	// Debug 
	std::cout << "The world was sent to the clients!" << std::endl;
}

void Server::Send(uint8_t* packet, size_t size) 
{
	for (auto client : clients)
	{
		client->write(reinterpret_cast<char*>(packet), static_cast<unsigned int>(size));
	}
	// Debug 
	std::cout << "Data was sent to the clients!" << std::endl;
}