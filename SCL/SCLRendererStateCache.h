#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	//��Ⱦ����״̬����
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
