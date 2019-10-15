#include "server.hpp"

Server::Server(std::string ip, int port)
{
	srvLoop = uvw::Loop::getDefault();
	std::shared_ptr<uvw::TCPHandle> tcp = srvLoop->resource<uvw::TCPHandle>();
	
	tcp->on<uvw::ListenEvent>([this](const uvw::ListenEvent&, uvw::TCPHandle& srv) {
		std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();
		
		client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent&, uvw::TCPHandle&) { ptr->close(); });
		client->on<uvw::EndEvent>([](const uvw::EndEvent&, uvw::TCPHandle& client) { client.close(); });
		
		srv.accept(*client);
		client->read();
		
		clients.push_back(client);

		});

	tcp->bind(ip, port);
	tcp->listen();
	
	srvLoop->run();
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

void Server::Send(uint8_t* packet, size_t size) 
{
	return;
}