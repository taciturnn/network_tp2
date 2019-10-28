#include <cassert>
#include <cmath>

#include "vector3.hpp"
#include "quaternion.hpp"

bool isnear(const Vector3& a, const Vector3& b)
{
	static float eps = 0.001;
	return std::abs(a.x - b.x) < eps && std::abs(a.y - b.y) < eps && std::abs(a.z - b.z) < eps;
}

bool isnear(const Quaternion& a, const Quaternion& b)
{
	static float eps = 0.001;
	return std::abs(a.x - b.x) < eps && std::abs(a.y - b.y) < eps && std::abs(a.z - b.z) < eps && std::abs(a.w - b.w) < eps;
}

class TestPackUnPack
{
public:
	static void TestVector3()
	{
		const Vector3
			v0 = { 0, 0, 0 },
			v1 = { -15, 10, 10 },
			v2 = { -500, 500, 500 },
			v3 = { 10.5, 0.29, -55.55 };

		assert(isnear(Vector3::Unpack(v0.Pack()), v0));
		assert(isnear(Vector3::Unpack(v1.Pack()), v1));
		assert(isnear(Vector3::Unpack(v2.Pack()), v2));
		assert(isnear(Vector3::Unpack(v3.Pack()), v3));
	}

	static void TestQuaternion()
	{
		const Quaternion
			v0 = { 1, 0, 0, 0},
			v1 = { 0, 1, 0, 0 },
			v2 = { 0, 0, 1, 0 },
			v3 = { 0, 0, 0, 1 };

		assert(isnear(Quaternion::Unpack(v0.Pack()), v0));
		assert(isnear(Quaternion::Unpack(v1.Pack()), v1));
		assert(isnear(Quaternion::Unpack(v2.Pack()), v2));
		assert(isnear(Quaternion::Unpack(v3.Pack()), v3));
	}
};

int main()
{
	TestPackUnPack::TestVector3();
	TestPackUnPack::TestQuaternion();
}