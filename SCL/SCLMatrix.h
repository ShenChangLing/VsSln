#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	
	template <int row,typename T>
	struct SCL_DLL Matrix
	{
		typedef Vector4<T> col_type;
	public:
		Matrix();
		~Matrix();
		Matrix(const T& s);

		inline const T* getDataPtr() const { return &(m[0].x); }
		T* getDataPtr() { return &(m[0].x); }

		Matrix& rotate(float radians, const Vector3<T>& axis);

		static  Matrix lookat(const Vector3<T> &eye, const Vector3<T>& lookPosition, const Vector3<T>& up);
		static Matrix perspective(float fov, float aspect, float nearDist, float farDist);

		col_type m[row];
	};




}