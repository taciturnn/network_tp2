#include "client.hpp"

Client::Client(std::string ip, int port)
{
	clientLoop = uvw::Loop::getDefault();
	auto tcp = clientLoop->resource<uvw::TCPHandle>();

	tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent&, uvw::TCPHandle&) { /* handle errors */ });

	tcp->on<uvw::ConnectEvent>([](const uvw::ConnectEvent&, uvw::TCPHandle& tcp) {
		auto dataWrite = std::unique_ptr<char[]>(new char[2]{ 'b', 'c' });
		tcp.write(std::move(dataWrite), 2);
		tcp.close();
		});

	tcp->on<uvw::DataEvent>([](const uvw::DataEvent& evt, uvw::TCPHandle&) {
		std::cout << evt.data << std::endl;
		});

	tcp->connect(std::string{ ip }, port);
	
	clientLoop->run();
}

bool Client::isAlive()
{
	return clientLoop->alive();
}

Client::~Client()
{
	clientLoop->stop();
	clientLoop->close();
}
