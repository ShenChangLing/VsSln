#pragma once
#include "SCLRenderTarget.h"

namespace SCL
{
	class SCL_DLL Window : public RenderTarget
	{
	public:
		Window(const char* name, int x, int y, int w, int h, bool fullscreen);
		virtual ~Window();

		//窗口是否关闭
		bool isClosed();

		void swapBuffers() override;

		void bindCurrentContext() override;
		void unbindCurrentContext() override;

	public:
		//通知窗口大小改变
		void _notifyWindowSizeChange();
	private:
		GLFWwindow* mGLFWWindow;
	};
}
