#include <iostream>
#include "client.hpp"
#include "server.hpp"

int main(int argc, char* argv[])
{
	std::shared_ptr<Server> server = nullptr;
	std::shared_ptr<Client> client = nullptr;

	if (argc != 4)
	{
		std::cout << "ERROR : ARGS REQUIRED ARE -> server/client ip port" << std::endl;
		return -1;
	}
	else
	{
		std::string appType = argv[1];
		std::string ip = argv[2];
		int port = std::stoi(std::string(argv[3]));

		if (appType == "server")
		{
			Server tmpServ = Server(ip, port);
			server = std::make_shared<Server>(tmpServ);
		}
		else if (appType == "client")
		{
			Client tmpClient = Client(ip, port);
			client = std::make_shared<Client>(tmpClient);
		}
		else
		{
			std::cout << "ERROR : Invalid application type." << std::endl;
			return -1;
		}
	}

	bool stop = false;
	while (!stop)
	{
		if (server != nullptr) { stop = !server->isAlive(); }
		else if (client != nullptr) { stop = !client->isAlive(); }
	}
}
