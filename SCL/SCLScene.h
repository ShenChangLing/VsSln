#pragma once

namespace SCL
{
	class SCL_DLL Scene
	{
	public:
		Scene();
		~Scene();

		/// @brief 创建相机
		Camera* createCamera(String name);

		//创建场景节点


	public:
		void renderScene(Camera* camera, Viewport* viewport);

	private:
		void _destroyAllCameras();

	protected:
		typedef std::unordered_map<String, Camera*> CameraList;

	private:
		Viewport* mCurrentViewport;
		Renderer* mRenderer;

		CameraList mCameras;
	};
}
