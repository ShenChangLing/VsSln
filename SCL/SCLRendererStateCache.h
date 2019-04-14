#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	//渲染器的状态缓存
	class RendererStateCache
	{
	public:
		RendererStateCache();
		~RendererStateCache();

		void setViewport(int x, int y, int width, int height);
		void setClearColor(const ColorValue& color);
	private:
		int mViewport[4];
		float mClearColorRGBA[4];
	};
}
