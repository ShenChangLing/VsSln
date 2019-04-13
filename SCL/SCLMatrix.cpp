#include "SCLPrerequisites.h"
#include "SCLMatrix.h"
#include "SCLInteriorHeader.h"

namespace SCL
{
	template Matrix<4, float>;

	template <int row, typename T>
	Matrix<row, T>::Matrix()
	{
	}


	template <int row, typename T>
	Matrix<row, T>::~Matrix()
	{
	}

	template <int row, typename T>
	Matrix<row, T>::Matrix(const T& s)
		: m{
			col_type(s, 0, 0, 0),
			col_type(0, s, 0, 0),
			col_type(0, 0, s, 0),
			col_type(0, 0, 0, s)
		}
	{
	}
	template<int row, typename T>
	Matrix<row,T> & Matrix<row, T>::rotate(float radians, const Vector3<T>& axis)
	{
		glm::mat4 temp = glm::make_mat4(getDataPtr());
		glm::vec3 tempvec3 = glm::make_vec3(axis.getDataPtr());
		
		temp = glm::rotate(temp, radians, tempvec3);
		memcpy(getDataPtr(), glm::value_ptr(temp), sizeof(temp));
		
		return *this;
	}

	template<int row, typename T>
	Matrix<row,T> Matrix<row, T>::lookat(const Vector3<T>& eye, const Vector3<T>& lookPosition, const Vector3<T>& up)
	{
		Matrix temp;

		glm::vec3 t_eye = glm::make_vec3(eye.getDataPtr());
		glm::vec3 t_look_pos = glm::make_vec3(lookPosition.getDataPtr());
		glm::vec3 t_up = glm::make_vec3(up.getDataPtr());

		glm::mat4 tempMat = glm::lookAt(t_eye, t_look_pos, t_up);
		memcpy(temp.getDataPtr(), glm::value_ptr(tempMat), sizeof(tempMat));

		return temp;
	}

	template<int row, typename T>
	Matrix<row,T> Matrix<row, T>::perspective(float fov, float aspect, float nearDist, float farDist)
	{
		Matrix temp;

		glm::mat4 tempMat = glm::perspective(fov, aspect, nearDist, farDist);
		memcpy(temp.getDataPtr(), glm::value_ptr(tempMat), sizeof(tempMat));

		return temp;
	}

}
