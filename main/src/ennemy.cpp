#include "ennemy.hpp"
#include "streams.hpp"

void Ennemy::Write(OutputStream& stream)
{
	uint64_t t_x = static_cast<uint64_t>((position_x + 500.) * 1000);
	uint64_t t_y = static_cast<uint64_t>((position_y + 500.) * 1000);
	uint64_t t_z = static_cast<uint64_t>((position_z + 500.) * 1000);

	uint64_t intToSend = t_x << 40 + t_y << 20 + t_z;

	stream.Write<uint64_t>(intToSend);
	return;
}

void Ennemy::Read(InputStream& stream)
{
	return;
}

void Ennemy::Destroy()
{
	return;
}
