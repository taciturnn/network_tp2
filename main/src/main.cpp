#include <iostream>
#include "client.hpp"
#include "server.hpp"

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "ERROR : ARGS REQUIRED ARE -> server/client ip port" << std::endl;
		return -1;
	}
	else
	{
		std::string appType = argv[1];
		std::string ip = argv[2];
		auto loop = uvw::Loop::getDefault();
		int port = std::stoi(std::string(argv[3]));

		if (appType == "server")
		{
			Server server = Server(ip, port, *loop);
			loop->run();
		}
		else if (appType == "client")
		{
			Client client = Client(ip, port, *loop);
			loop->run();

			loop->walk([](uvw::BaseHandle& h) { 
				h.close(); 
			});

			while (loop->alive())
			{
				// Do nothing
			}
		}
		else
		{
			std::cout << "ERROR : Invalid application type." << std::endl;
			return -1;
		}
	}
}
