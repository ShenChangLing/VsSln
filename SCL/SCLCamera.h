#pragma once
#include "SCLPrerequisites.h"


namespace SCL
{
	class SCL_DLL Camera
	{
	public:
		Camera(String name, Scene* scene);
		~Camera();

		void renderScene(Viewport* viewport);

		const String& getName() const { return mName; }
		Scene* getScene() { return mScene; }

		void lookat(float x, float y, float z);
		void lookat(const Vector3f& position);

		void setPosition(float x, float y, float z);
		void setPosition(const Vector3f& position);

		const Matrix4f& getCameraView();
		const Matrix4f& getCameraPerspective();

	private:
		void _updateCamera(); //内部更新摄像机
	private:
		String mName;
		Scene* mScene;

		float mFov; //角度默认45
		float mFarDist;
		float mNearDist;

		float mAspect; //宽高比例

		Vector3f mPosition; //位置
		Vector3f mLookPosition; //所看位置
		Vector3f mDirection; //方向
		Vector3f mUP; //上方向

		Vector3f mCameraRightDirection; //右方向
		Vector3f mCameraUpDirection; //摄像机的上方向

	private:
		bool mIsUpdateCamera;
		Matrix4f mCameraViewMat;
		Matrix4f mCameraPerspective;
	};
}
