#include "SCLPrerequisites.h"
#include "SCLImage.h"

#include "SCLInteriorHeader.h"

namespace SCL
{
	Image::Image()
	{
		mData = nullptr;
		mDataLength = 0;

		mWidth = mHeight = 0;
	}

	Image::~Image()
	{
		if (mData)
		{
			free(mData);
			mData = nullptr;
		}
	}

	void Image::initFromFile(const char* filePath)
	{
		FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filePath);
		if (FIF_UNKNOWN == fif)
			return;

		if (!FreeImage_FIFSupportsReading(fif))
			return;

		FIBITMAP* fib = FreeImage_Load(fif, filePath);

		mWidth = FreeImage_GetWidth(fib);
		mHeight = FreeImage_GetHeight(fib);

		FREE_IMAGE_COLOR_TYPE fict = FreeImage_GetColorType(fib);
		FREE_IMAGE_TYPE fit = FreeImage_GetImageType(fib);

		auto size = FreeImage_GetDIBSize(fib);
		auto msize = FreeImage_GetMemorySize(fib);
		auto bpp = FreeImage_GetBPP(fib);
		auto line = FreeImage_GetLine(fib);
		auto pitch = FreeImage_GetPitch(fib);

		size = pitch * mHeight;
		mData = (unsigned char *)malloc(size);
		memcpy(mData, FreeImage_GetBits(fib), size);

		FreeImage_Unload(fib);
	}
}