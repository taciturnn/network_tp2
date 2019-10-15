#include <iostream>

#include <uvw.hpp>
#include <memory>
#include <string>

class Client
{
public:
	Client(std::string ip, int port);
	~Client();

	bool isAlive();

private:

	std::shared_ptr<uvw::Loop> clientLoop;
};