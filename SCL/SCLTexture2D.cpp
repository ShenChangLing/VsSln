#include "SCLPrerequisites.h"
#include "SCLTexture2D.h"

#include "SCLImage.h"
#include "SCLInteriorHeader.h"

namespace SCL
{

	Texture2D::Texture2D(Image* image)
	{
		glGenTextures(1, &mTextureID);
		glBindTexture(GL_TEXTURE_2D, mTextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getWidth(), 0, GL_BGR, GL_UNSIGNED_BYTE, image->getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}


	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &mTextureID);
	}

	void Texture2D::bind()
	{
		glBindTexture(GL_TEXTURE_2D, mTextureID);
	}

}