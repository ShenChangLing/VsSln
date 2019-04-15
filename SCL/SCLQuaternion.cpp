#include "SCLPrerequisites.h"
#include "SCLQuaternion.h"
#include "SCLInteriorHeader.h"

namespace SCL
{
	Quaternion::Quaternion(float _x, float _y, float _z, float _w)
		: w(_w), x(_x), y(_y), z(_z)
	{
	}

	Quaternion::Quaternion(const Quaternion& quat)
		: Quaternion(quat.x, quat.y, quat.z, quat.w)
	{
	}

	Quaternion::~Quaternion()
	{
	}

	Quaternion Quaternion::operator*(const Quaternion& quat) const
	{
		return Quaternion
		(
			w * quat.x + x * quat.w + y * quat.z - z * quat.y,
			w * quat.y + y * quat.w + z * quat.x - x * quat.z,
			w * quat.z + z * quat.w + x * quat.y - y * quat.x,
			w * quat.w - x * quat.x - y * quat.y - z * quat.z
		);
	}

	Quaternion Quaternion::operator*(const float& s) const
	{
		return Quaternion(x * s, y * s, z * s, w * s);
	}

	Quaternion& Quaternion::operator*=(const Quaternion& quat)
	{
		*this = *this * quat;
		return *this;
	}
}
