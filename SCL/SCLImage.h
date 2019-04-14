#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	class Image
	{
	public:
		Image();
		~Image();

		void initFromFile(const char* filePath);
		unsigned char* getData() { return mData; }
		int getWidth() const { return mWidth; }
		int getHeight() const { return mHeight; }

	private:
		unsigned char* mData;
		unsigned int mDataLength;

		int mWidth;
		int mHeight;
	};
}
