#pragma once

#include <iostream>

#include <uvw.hpp>
#include <memory>
#include <vector>
#include <string>
#include "replication_manager.hpp"

#include "player.hpp"
#include "ennemy.hpp"

class Server
{
public:
	Server(std::string ip, int port, uvw::Loop& loop);
	~Server() = default;

	void SendWorld();
	void Send(uint8_t* packet, size_t size);

private:
	std::vector<std::unique_ptr<Player>> myPlayers;
	std::vector< std::unique_ptr<Ennemy>> myEnnemies;

	ReplicationManager master;
	std::vector<std::shared_ptr<uvw::TCPHandle>> clients;
};