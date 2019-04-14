#include "SCLPrerequisites.h"
#include "SCLViewport.h"
#include "SCLCamera.h"
#include "SCLRenderTarget.h"

namespace SCL
{
	Viewport::Viewport(Camera* camera, RenderTarget* rt, float left, float top, float width, float height)
		: mCamera(camera),
		  mRenderTarget(rt),
		  mRelativeLeft(left), mRelativeTop(top), mRelativeWidth(width), mRelativeHeight(height)
	{
		_updateDimensions();
	}


	Viewport::~Viewport()
	{
	}

	void Viewport::update()
	{
		if (!mCamera)
			return;

		mCamera->renderScene(this);
	}

	void Viewport::clear(uint clearMask)
	{
	}

	void Viewport::getActualDimensions(int& left, int& top, int& width, int& height) const
	{
		left = mActualLeft;
		top = mActualTop;

		width = mActualWidth;
		height = mActualHeight;
	}

	void Viewport::_updateDimensions()
	{
		int width = mRenderTarget->getWidth();
		int height = mRenderTarget->getHeight();

		mActualLeft = static_cast<int>(mRelativeLeft * width);
		mActualTop = static_cast<int>(mRelativeTop * height);

		mActualWidth = static_cast<int>(mRelativeWidth * width);
		mActualHeight = static_cast<int>(mRelativeHeight * height);
	}
}
