#include "client.hpp"
#include <string>
#include <iostream>
#include "streams.hpp"
#include "gsl/gsl"
#include "class_registry.hpp"
#include "ennemy.hpp"
#include "player.hpp"

Client::Client(std::string ip, int port, uvw::Loop& clientLoop)
{
	slave = ReplicationManager();
	ClassRegistry::GetInstance()->Register(Player());
	ClassRegistry::GetInstance()->Register(Ennemy());

	auto tcp = clientLoop.resource<uvw::TCPHandle>();

	tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent& e, uvw::TCPHandle&) { std::cout << e.name() << ": " << e.what() << std::endl; });

	tcp->on<uvw::ConnectEvent>([ip, port](const uvw::ConnectEvent&, uvw::TCPHandle& tcp) {
		// Debug
		std::cout << "Client is connected to " << ip << ":" << std::to_string(port) << std::endl;
		tcp.close();
		});

	tcp->on<uvw::DataEvent>([this](const uvw::DataEvent& evt, uvw::TCPHandle&) {
		std::cout << "Client has received new data!" << std::endl;
		InputStream stream(gsl::make_span(evt.data.get(), evt.length));
		slave.Replicate(stream);
		slave.DisplayWorld();
		});

	tcp->connect(ip, port);
}