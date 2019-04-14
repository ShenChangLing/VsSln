#include "SCLPrerequisites.h"
#include "SCLScene.h"
#include "SCLCamera.h"
#include "SCLViewport.h"
#include "SCLRenderer.h"
#include "SCLRoot.h"
#include "SCLInteriorHeader.h"

namespace SCL
{
	Scene::Scene()
	{
		mCurrentViewport = nullptr;
		mRenderer = Root::getSingletonPtr()->getRenderer();

		mCameras.clear();
	}

	Scene::~Scene()
	{
		_destroyAllCameras();

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

	void Scene::renderScene(Camera* camera, Viewport* viewport)
	{
		mCurrentViewport = viewport;

		mRenderer->setViewport(mCurrentViewport);

		mRenderer->clear(Renderer::CBB_Color, mCurrentViewport->getBackgroundColorValue());
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
