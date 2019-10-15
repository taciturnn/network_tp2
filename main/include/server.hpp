#pragma once

#include <iostream>

#include <uvw.hpp>
#include <memory>
#include <vector>
#include <string>

class Server
{
public:
	Server(std::string ip, int port);
	~Server();

	void Send(uint8_t* packet, size_t size);
	bool isAlive();

private:
	std::shared_ptr<uvw::Loop> srvLoop;
	std::vector<std::shared_ptr<uvw::TCPHandle>> clients;

};