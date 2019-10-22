#include <iostream>

#include <uvw.hpp>
#include <memory>
#include <string>
#include "replication_manager.hpp"

class Client
{
public:
	Client(std::string ip, int port, uvw::Loop& loop);
	~Client() = default;

private:
	ReplicationManager slave;
};