#include "SCLPrerequisites.h"
#include "SCLWindow.h"

#include "SCLInteriorHeader.h"

namespace SCL
{
	void windowcloseCallback(GLFWwindow* window)
	{
	}

	void windowsizeCallback(GLFWwindow* window, int width, int height)
	{
		Window* myWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		myWindow->_notifyWindowSizeChange();
	}

	Window::Window(const char* name, int x, int y, int w, int h, bool fullscreen)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		int mx, my, mw, mh;
		glfwGetMonitorWorkarea(monitor, &mx, &my, &mw, &mh);

		int cx = x, cy = y;

		if (x < 0)
			cx = static_cast<int>((mw - w) * 0.5f);

		if (y < 0)
			cy = static_cast<int>((mh - h) * 0.5f);

		mGLFWWindow = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
		glfwSetWindowPos(mGLFWWindow, cx, cy);
		glfwMakeContextCurrent(mGLFWWindow);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glfwSetWindowUserPointer(mGLFWWindow, this);

		glfwSetWindowCloseCallback(mGLFWWindow, windowcloseCallback);
		glfwSetWindowSizeCallback(mGLFWWindow, windowsizeCallback);

		glfwSwapInterval(1); //垂直同步
	}

	Window::~Window()
	{
		glfwDestroyWindow(mGLFWWindow);
		mGLFWWindow = nullptr;
	}

	bool Window::isClosed()
	{
		return glfwWindowShouldClose(mGLFWWindow);
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(mGLFWWindow);
	}

	void Window::unbindCurrentContext()
	{
		glfwMakeContextCurrent(nullptr);
	}

	void Window::_notifyWindowSizeChange()
	{
		glfwGetWindowSize(mGLFWWindow, &mWidth, &mHeight);
	}

	void Window::bindCurrentContext()
	{
		glfwMakeContextCurrent(mGLFWWindow);
	}
}