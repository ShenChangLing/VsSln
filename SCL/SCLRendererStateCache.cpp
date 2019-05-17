#include "SCLPrerequisites.h"
#include "SCLRendererStateCache.h"
#include "SCLInteriorHeader.h"
#include "SCLColorValue.h"

namespace SCL
{
	RendererStateCache::RendererStateCache()
	{
		memset(mViewport, 0, sizeof(int) * 4);
		memset(mClearColorRGBA, 0, sizeof(float) * 4);
		mClearColorRGBA[0] = -10.0f; //防止BUG
	}

	RendererStateCache::~RendererStateCache()
	{
	}

	void RendererStateCache::setViewport(int x, int y, int width, int height)
	{
		if (mViewport[0] != x || mViewport[1] == y || mViewport[2] == width || mViewport[3] == height)
		{
			mViewport[0] = x;
			mViewport[1] = y;
			mViewport[2] = width;
			mViewport[3] = height;

			glViewport(x, y, width, height);
			glScissor(x, y, width, height);
		}
	}

	void RendererStateCache::setClearColor(const ColorValue& color)
	{
		if (mClearColorRGBA[0] != color.r ||
			mClearColorRGBA[1] != color.g ||
			mClearColorRGBA[2] != color.b ||
			mClearColorRGBA[3] != color.a)
		{
			mClearColorRGBA[0] = color.r;
			mClearColorRGBA[1] = color.g;
			mClearColorRGBA[2] = color.b;
			mClearColorRGBA[3] = color.a;

			glClearColor(color.r, color.g, color.g, color.a);
		}
	}
}