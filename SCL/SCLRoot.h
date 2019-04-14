#pragma once
#include "SCLPrerequisites.h"
#include "SCLSingleton.h"

namespace SCL
{
	class SCL_DLL Root : public Singleton<Root>
	{
	public:
		Root();
		~Root();

		Window* createWindow(const char* name, int x, int y, int width, int height, bool fullscreen = false);
		void destroyWindow(Window* window);
		void destroyWindows();

		Scene* createScene();
		void destroyScene(Scene* scene);

		Renderer* getRenderer() { return mRenderer; }

		void run();
		void renderOneFrame(); //绘制一帧

	protected:
		void _clearCloseWindows();
		void _destroyAllScene();

	protected:
		typedef std::list<Window*> WindowList;
		typedef std::list<Scene*> SceneList;
		WindowList* mWindows;

		Renderer* mRenderer; //渲染器

		SceneList* mScenes;
	};
}
