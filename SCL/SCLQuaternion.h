#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	//四元数
	class SCL_DLL Quaternion
	{
	public:
		Quaternion(float _x, float _y, float _z, float _w);
		Quaternion(const Quaternion& quat);
		~Quaternion();

		Quaternion& operator=(const Quaternion& quat)
		{
			w = quat.w;
			x = quat.x;
			y = quat.y;
			z = quat.z;

			return *this;
		}

		Quaternion operator*(const Quaternion& quat) const;
		Quaternion operator*(const float& s) const;
		Vector3<float> operator*(const Vector3<float>& vector3) const;
		Quaternion& operator*=(const Quaternion& quat);

		float dot(const Quaternion& quat) const
		{
			return w * quat.w + x * quat.x + y * quat.y + z * quat.z;
		}

		float Norm() const
		{
			return std::sqrt(dot(*this));
		}

		float normalise()
		{
			float len = Norm();

			*this = *this * (1.0f / len);

			return len;
		}

		static const Quaternion IDENTITY;
		static const Quaternion ZERO;

		const float* getDataPtr() const { return &x; }

	public:
		float x, y, z, w;
	};
}
