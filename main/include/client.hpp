#include <iostream>

#include <uvw.hpp>
#include <memory>
#include <string>
#include "replication_manager.hpp"

class Client
{
public:
	Client(std::string ip, int port, uvw::Loop& loop);
	~Client();

	bool isAlive();

private:
	ReplicationManager slave;
	std::shared_ptr<uvw::Loop> clientLoop;
};