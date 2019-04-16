#include "SCLPrerequisites.h"
#include "SCLScene.h"
#include "SCLCamera.h"
#include "SCLViewport.h"
#include "SCLRenderer.h"
#include "SCLRoot.h"
#include "SCLInteriorHeader.h"
#include "SCLSceneNode.h"

namespace SCL
{
	Scene::Scene()
	{
		mCurrentViewport = nullptr;
		mRenderer = Root::getSingletonPtr()->getRenderer();

		mCameras.clear();
		mSceneNodes.clear();

		mSceneNodeRoot = this->createSceneNode();
	}

	Scene::~Scene()
	{
		_destroyAllCameras();

		this->destroySceneNode(mSceneNodeRoot);
		mSceneNodeRoot = nullptr;

		mCurrentViewport = nullptr;
		mRenderer = nullptr;
	}

	Camera* Scene::createCamera(String name)
	{
		auto iter = mCameras.find(name);
		if (iter != mCameras.end())
		{
			return iter->second;
		}

		Camera* camera = new Camera(name, this);
		mCameras.insert(CameraList::value_type(name, camera));
		return camera;
	}

	SceneNode* Scene::createSceneNode()
	{
		SceneNode* sn = new SceneNode(this);

		{
			SCL_AUTO_LOCK_MUTEX;
			mSceneNodes.push_back(sn);
		}

		return sn;
	}

	void Scene::destroySceneNode(SceneNode* scene_node)
	{
		{
			SCL_AUTO_LOCK_MUTEX;
			mSceneNodes.remove(scene_node);
		}
		delete scene_node;
	}

	void Scene::renderScene(Camera* camera, Viewport* viewport)
	{
		mCurrentViewport = viewport;

		mRenderer->setViewport(mCurrentViewport);

		mRenderer->clear(Renderer::CBB_Color, mCurrentViewport->getBackgroundColorValue());

		//更新所有的节点信息
		getSceneNodeRoot()->_update();
	}

	void Scene::_destroyAllCameras()
	{
		for (auto camera : mCameras)
		{
			delete camera.second;
		}
		mCameras.clear();
	}
}
