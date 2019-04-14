#include "SCLPrerequisites.h"
#include "SCLRenderTarget.h"
#include "SCLViewport.h"
#include <glfw3.h>

namespace SCL
{
	RenderTarget::RenderTarget()
	{
		mName = "null";
		mWidth = 800;
		mHeight = 600;

		mViewports = new ViewportList();

		mPrioritised = 0;
	}


	RenderTarget::~RenderTarget()
	{
		for (auto i : *mViewports)
		{
			delete (i.second);
		}
		mViewports->clear();
		delete mViewports;
	}

	Viewport* RenderTarget::addViewport(Camera* camera, int z, float left, float top, float width, float height)
	{
		if (mViewports->find(z) != mViewports->end())
		{
			return nullptr; //不能同时增加相同的Z序列
		}

		Viewport* viewport = new Viewport(camera, this, left, top, width, height);

		mViewports->insert(ViewportList::value_type(z, viewport));

		return viewport;
	}

	void RenderTarget::update()
	{
		//开始更新所有的视口
		for (auto i : *mViewports)
		{
			(i.second)->update();
		}

		swapBuffers();
	}
}
