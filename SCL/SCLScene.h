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
		SceneNode* createSceneNode();
		//销毁场景节点
		void destroySceneNode(SceneNode* scene_node);
		SceneNode* getSceneNodeRoot() { return mSceneNodeRoot; }

	public:
		void renderScene(Camera* camera, Viewport* viewport);

	private:
		void _destroyAllCameras();

	protected:
		typedef std::unordered_map<String, Camera*> CameraList;

	private:
		SCL_AUTO_MUTEX;
		Viewport* mCurrentViewport;
		Renderer* mRenderer;

		CameraList mCameras;
		SceneNodeList mSceneNodes;

		SceneNode* mSceneNodeRoot; //场景的根节点
	};
}
