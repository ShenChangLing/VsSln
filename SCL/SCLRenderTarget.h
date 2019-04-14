#pragma once

namespace SCL
{
	class SCL_DLL RenderTarget
	{
	public:
		RenderTarget();
		virtual ~RenderTarget();

		virtual const String& getName() const { return mName; }

		virtual const int getWidth() const { return mWidth; }
		virtual const int getHeight() const { return mHeight; }

		virtual void swapBuffers() = 0;

		virtual Viewport* addViewport(Camera* camera, int z = 0, float left = 0.0f, float top = 0.0f,
		                              float width = 1.0f, float height = 1.0f);

		const uchar getPrioritised() const { return mPrioritised; }

		void update();
		virtual void bindCurrentContext() = 0;
		virtual void unbindCurrentContext() = 0;

	protected:
		String mName;
		int mWidth;
		int mHeight;

		typedef std::map<int, Viewport*> ViewportList;
		ViewportList* mViewports;

		uchar mPrioritised; //优先级，默认为0
	};
}
