#include "SCLPrerequisites.h"
#include "SCLShaderProgram.h"

#include "SCLInteriorHeader.h"

namespace SCL
{
	ShaderProgram::ShaderProgram(const char* vsfilepath, const char* fsfilepath)
		: ShaderProgram()
	{
		std::ifstream ivs, ifs;
		ivs.open(vsfilepath);
		assert(ivs.is_open());

		ifs.open(fsfilepath);
		assert(ifs.is_open());

		std::stringstream ivsstream, ifsstream;

		ivsstream << ivs.rdbuf();
		ifsstream << ifs.rdbuf();

		ivs.close();
		ifs.close();

		init(ivsstream.str().c_str(), ifsstream.str().c_str());
	}

	ShaderProgram::ShaderProgram()
		: mProgram(0)
	{
	}

	ShaderProgram::~ShaderProgram()
	{
		if (mProgram)
		{
			glDeleteProgram(mProgram);
			mProgram = 0;
		}
	}

	void ShaderProgram::init(const char* vssource, const char* fssource)
	{
		GLuint vs, fs;
		vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vssource, nullptr);
		glCompileShader(vs);

		GLint errorID = 0;
		glGetShaderiv(vs, GL_COMPILE_STATUS, &errorID);
		if (!errorID)
		{
			char errorStr[512];
			glGetShaderInfoLog(vs, 512, nullptr, errorStr);
#ifdef _WIN32
			OutputDebugString(errorStr);
			OutputDebugString("\n");
#endif
		}

		fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fssource, nullptr);
		glCompileShader(fs);
		glGetShaderiv(fs, GL_COMPILE_STATUS, &errorID);
		if (!errorID)
		{
			char errorStr[512];
			glGetShaderInfoLog(vs, 512, nullptr, errorStr);
#ifdef _WIN32
			OutputDebugString(errorStr);
			OutputDebugString("\n");
#endif
		}

		mProgram = glCreateProgram();
		glAttachShader(mProgram, vs);
		glAttachShader(mProgram, fs);
		glLinkProgram(mProgram);

		glGetProgramiv(mProgram, GL_LINK_STATUS, &errorID);
		if (!errorID)
		{
			char errorStr[512];
			glGetProgramInfoLog(vs, 512, nullptr, errorStr);
#ifdef _WIN32
			OutputDebugString(errorStr);
			OutputDebugString("\n");
#endif
		}

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	int ShaderProgram::getUniformLocation(const char* name)
	{
		return glGetUniformLocation(mProgram, name);
	}

	void ShaderProgram::setUniformMatrix4fv(int location, const Matrix4f& mat)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, mat.getDataPtr());
	}

	void ShaderProgram::use()
	{
		assert(mProgram);
		glUseProgram(mProgram);
	}
}