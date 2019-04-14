#pragma once
#include "SCLPrerequisites.h"


namespace SCL
{
	class Texture2D
	{
	public:
		Texture2D(Image* image);
		~Texture2D();

		void bind();

	private:
		unsigned int mTextureID;
	};
}
