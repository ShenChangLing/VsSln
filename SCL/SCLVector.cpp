#include "SCLPrerequisites.h"
#include "SCLVector.h"
#include "SCLInteriorHeader.h"

namespace SCL
{
	template Vector2<float>;
	template Vector2<double>;
	template Vector2<int>;

	template Vector3<float>;
	template Vector3<double>;
	template Vector3<int>;

	template Vector4<float>;
	template Vector4<double>;
	template Vector4<int>;

	template <typename T>
	Vector2<T>::Vector2(T _x, T _y)
	{
		x = _x;
		y = _y;
	}

	///////////////////////////////////////////

	template <typename T>
	const Vector3<T> Vector3<T>::ZERO = Vector3<T>(0, 0, 0);

	template <typename T>
	Vector3<T>::Vector3(T _x, T _y, T _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	template <typename T>
	Vector3<T>& Vector3<T>::normalize()
	{
		glm::vec3 temp = glm::make_vec3(this->getDataPtr());
		temp = glm::normalize(temp);

		memcpy(getDataPtr(), value_ptr(temp), sizeof(temp));

		return *this;
	}

	template <typename T>
	Vector3<T>& Vector3<T>::cross(const Vector3<T>& v)
	{
		glm::vec3 v1 = glm::make_vec3(v.getDataPtr());
		glm::vec3 v2 = glm::make_vec3(v.getDataPtr());

		v1 = glm::cross(v1, v2);

		memcpy(getDataPtr(), value_ptr(v1), sizeof(v1));

		return *this;
	}

	template <typename T>
	Vector3<T> Vector3<T>::operator-(const Vector3<T>& v) const
	{
		Vector3<T> rv(x - v.x, y - v.y, z - v.z);
		return rv;
	}

	template <typename T>
	Vector3<T> Vector3<T>::operator-(const Vector3<T>& v)
	{
		Vector3<T> rv(x - v.x, y - v.y, z - v.z);
		return rv;
	}

	template <typename T>
	Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	template <typename T>
	Vector3<T> Vector3<T>::operator+(const Vector3<T>& v)
	{
		Vector3<T> rv(x + v.x, y + v.y, z + v.z);
		return rv;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator+=(const Vector3<T> v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	template <typename T>
	Vector3<T> Vector3<T>::operator*(const Vector3<T>& v) const
	{
		return Vector3<T>(x * v.x, y * v.y, z * v.z);;
	}

	template <typename T>
	Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator=(const Vector3<T> v)
	{
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	///////////////////////////////////////////

	template <typename T>
	Vector4<T>::Vector4(T _x, T _y, T _z, T _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
}
