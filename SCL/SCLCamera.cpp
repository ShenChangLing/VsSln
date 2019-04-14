#include "SCLPrerequisites.h"
#include "SCLCamera.h"
#include "SCLViewport.h"
#include "SCLScene.h"
#include "SCLInteriorHeader.h"

namespace SCL
{
	Camera::Camera(String name, Scene* scene)
		: mName(name),
		  mScene(scene),
		  mFov(45),
		  mFarDist(1000.0f),
		  mNearDist(0.1f),
		  mAspect(1.33333f),
		  mPosition(0, 1, 0),
		  mDirection(0, 0, -1),
		  mUP(0, 1, 0),
		  mCameraRightDirection(0, 0, 0),
		  mCameraUpDirection(0, 0, 0),
		  mIsUpdateCamera(true),
		  mCameraViewMat(1),
		  mCameraPerspective(1)
	{
	}


	Camera::~Camera()
	{
	}

	void Camera::renderScene(Viewport* viewport)
	{
		mScene->renderScene(this, viewport);
	}

	void Camera::lookat(float x, float y, float z)
	{
		lookat(Vector3f(x, y, z));
	}

	void Camera::lookat(const Vector3f& position)
	{
		mLookPosition = position;

		mDirection = mLookPosition - mPosition; //眼睛的位置减去眼睛所看位置，得到方向
		mDirection.normalize();

		mCameraRightDirection = mUP;
		mCameraRightDirection.cross(mDirection).normalize();

		mCameraUpDirection = mDirection;
		mCameraUpDirection.cross(mCameraRightDirection);

		mIsUpdateCamera = true;
	}

	void Camera::setPosition(float x, float y, float z)
	{
		setPosition(Vector3f(x, y, z));
	}

	void Camera::setPosition(const Vector3f& position)
	{
		mPosition = position;

		mIsUpdateCamera = true;
	}

	const Matrix4f& Camera::getCameraView()
	{
		_updateCamera();

		return mCameraViewMat;
	}

	const Matrix4f& Camera::getCameraPerspective()
	{
		_updateCamera();

		return mCameraPerspective;
	}

	void Camera::_updateCamera()
	{
		if (!mIsUpdateCamera)
			return;

		//更新
		mCameraViewMat = Matrix4f::lookat(mPosition, mLookPosition, mUP);
		mCameraPerspective = Matrix4f::perspective(mFov, mAspect, mNearDist, mFarDist);
	}
}
