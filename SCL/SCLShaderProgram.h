#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const char* vsfilepath, const char* fsfilepath);
		ShaderProgram();
		~ShaderProgram();

		void init(const char* vssource, const char* fssource);
		int getUniformLocation(const char* name);
		void setUniformMatrix4fv(int location, const Matrix4f& mat);

		void use();

	private:
		uint mProgram;
	};
}
