#pragma once

#include <cstdint>
#include "streams.hpp"

using ReplicationClassID = uint32_t;

#define REPLICATED(id,className)                                    \
enum : ReplicationClassID{mClassID = id};                           \
virtual ReplicationClassID ClassID() const  { return mClassID;}     \
static GameObject* CreateInstance() {return new className();}       \

class GameObject
{
public:
	virtual void Destroy();
	virtual void Write(const OutputStream& stream);
	virtual void Read(const InputStream& stream);
};