#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	template <typename T>
	struct SCL_DLL Vector2
	{
	public:
		Vector2(T _x, T _y);
		Vector2() { x = y = 0; }

		~Vector2()
		{
		}

		T x, y;
	};

	template <typename T>
	struct SCL_DLL Vector3
	{
		Vector3(T _x, T _y, T _z);
		Vector3() { x = y = z = 0; }

		const T* getDataPtr() const { return &x; }
		T* getDataPtr() { return &x; }

		Vector3<T>& normalize(); //一致化,标准化
		Vector3<T>& cross(const Vector3<T>& v); //×乘

		Vector3<T> operator-(const Vector3<T>& v) const;
		Vector3<T> operator-(const Vector3<T>& v);
		Vector3<T>& operator-=(const Vector3<T>& v);
		Vector3<T> operator+(const Vector3<T>& v);
		T x, y, z;
	};

	template <typename T>
	struct SCL_DLL Vector4
	{
		Vector4(T _x, T _y, T _z, T _w);
		Vector4() { x = y = z = 0; }

		T x, y, z, w;
	};
}
