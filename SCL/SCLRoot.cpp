#include "SCLPrerequisites.h"
#include "SCLRoot.h"
#include "SCLWindow.h"
#include "SCLShaderProgram.h"
#include "SCLImage.h"
#include "SCLTexture2D.h"
#include "SCLRenderer.h"
#include "SCLScene.h"
#include "SCLNetworkManager.h"

#include "SCLInteriorHeader.h"

#ifdef WIN32
#include <direct.h>
#include <shellapi.h>
#endif

template <>
SCL::Root* SCL::Singleton<SCL::Root>::mSingleton = nullptr;

namespace SCL
{
	void _glfw_error_callback(int error, const char* description)
	{
		std::string errorStr = description;
		errorStr += "\n";
#if defined(_WIN32) && defined(_DEBUG)
		OutputDebugString(errorStr.c_str());
#endif
	}

	void _testOpenGL()
	{
		//
		GLFWwindow* window = glfwCreateWindow(800, 600, "opengl", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glClearColor(0.2f, 0.2f, 0.3f, 1);
		glViewport(0, 0, 800, 600);
		glEnable(GL_DEPTH_TEST);

		float vertices[] = {
			0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
			-0.5f, 0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 1.0f // top left
		};
		unsigned int indices[] = {
			// note that we start from 0!
			0, 1, 3, // first Triangle
			1, 2, 3 // second Triangle
		};

		GLuint VBO, VAO, EBO;
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, nullptr);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		ShaderProgram sp("../Res/GLSL/glsl0.vert", "../Res/GLSL/glsl0.frag");

		Image image;
		image.initFromFile("../Res/0.jpg");

		Texture2D texture(&image);

		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//glm::mat4 transform = glm::mat4(1.0f);
			//transform = rotate(transform, (float)glfwGetTime(), glm::vec3(0, 0, 1.0f));

			Matrix4f matTransform(1.0f);
			matTransform.rotate((float)glfwGetTime(), Vector3f(0.0f, 0.0f, 1.0f));
			sp.setUniformMatrix4fv(sp.getUniformLocation("transform"), matTransform);

			sp.use();
			glBindVertexArray(VAO);
			texture.bind();

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			glfwSwapBuffers(window);
		}

		glfwDestroyWindow(window);
	}

	void testFreetype2()
	{
		FT_Library ft_lib;
		FT_Init_FreeType(&ft_lib);

		FT_Face ft_face;
		FT_New_Face(ft_lib, "../Res/0.otf", 0, &ft_face);

		FT_Set_Pixel_Sizes(ft_face, 0, 12);

		FT_UInt index = FT_Get_Char_Index(ft_face, 'a');

		FT_Load_Glyph(ft_face, index, FT_LOAD_DEFAULT);
		FT_Render_Glyph(ft_face->glyph, FT_RENDER_MODE_NORMAL);

		FT_Done_FreeType(ft_lib);
	}

	void _init_of_glog()
	{
		//日志库初始化
		google::InitGoogleLogging("");
		google::SetLogFilenameExtension(".txt");
		FLAGS_log_dir = "./AppRunLog";
#ifdef WIN32
		//删除文件夹，如果存在
		SHFILEOPSTRUCT shfileopstruct = {};
		shfileopstruct.wFunc = FO_DELETE;
		shfileopstruct.fFlags = FOF_NO_UI;
		shfileopstruct.pFrom = FLAGS_log_dir.c_str();
		shfileopstruct.pTo = nullptr;
		SHFileOperation(&shfileopstruct);
		//创建文件夹
		_mkdir(FLAGS_log_dir.c_str());
#endif
		FLAGS_logtostderr = false;
		FLAGS_alsologtostderr = false;
		FLAGS_log_prefix = true;
	}

	Root::Root()
	{
		_init_of_glog();

#ifdef FREEIMAGE_LIB
		FreeImage_Initialise(true);
#endif

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwSetErrorCallback(_glfw_error_callback);

		mNetworkManager = new NetworkManager();

		mWindows = new WindowList();
		mRenderer = new Renderer();

		mScenes = new SceneList();

		//_testOpenGL();
		//testFreetype2();
	}

	Root::~Root()
	{
		delete mNetworkManager;
		mNetworkManager = nullptr;

		destroyWindows();
		delete mScenes;
		mScenes = nullptr;
		delete mWindows;
		mWindows = nullptr;
		delete mRenderer;
		mRenderer = nullptr;

		glfwTerminate();
#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
#endif

		//关闭日志库
		google::ShutdownGoogleLogging();
	}

	Window* Root::createWindow(const char* name, int x, int y, int width, int height, bool fullscreen)
	{
		Window* window = nullptr;
		window = new Window(name, x, y, width, height, fullscreen);
		mWindows->push_back(window);

		//绑定到渲染目标
		mRenderer->attachRenderTarget(*window);

		return window;
	}

	void Root::destroyWindow(Window* window)
	{
		mRenderer->detachRenderTarget(window->getName());
		mWindows->remove(window);
		delete window;
	}

	void Root::destroyWindows()
	{
		for (auto window : *mWindows)
		{
			destroyWindow(window);
		}
	}

	Scene* Root::createScene()
	{
		Scene* scene = new Scene();

		mScenes->push_back(scene);

		return scene;
	}

	void Root::destroyScene(Scene* scene)
	{
		mScenes->remove(scene);
		delete scene;
	}

	void Root::run()
	{
		while (!mWindows->empty())
		{
			glfwPollEvents();

			_clearCloseWindows();
			renderOneFrame();
		}
	}

	void Root::renderOneFrame()
	{
		mRenderer->updateAllRenderTargets();
	}

	void Root::_clearCloseWindows()
	{
		static WindowList removeWindows;
		removeWindows.clear();
		for (auto i : *mWindows)
		{
			if (i->isClosed())
			{
				removeWindows.push_back(i);
			}
		}

		for (auto window : removeWindows)
		{
			destroyWindow(window);
		}
	}

	void Root::_destroyAllScene()
	{
		for (auto scene : *mScenes)
		{
			delete scene;
		}
		mScenes->clear();
	}
}