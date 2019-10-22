#pragma once

#include <iostream>

#include <uvw.hpp>
#include <memory>
#include <vector>
#include <string>
#include "replication_manager.hpp"

class Server
{
public:
	Server(std::string ip, int port, uvw::Loop& loop);
	~Server();

	void SendWorld();
	void Send(uint8_t* packet, size_t size);
	bool isAlive();

private:
	ReplicationManager master;
	std::vector<std::shared_ptr<uvw::TCPHandle>> clients;
};