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
		void _updateCamera();//�ڲ����������
	private:
		String mName;
		Scene* mScene;

		float mFov;//�Ƕ�Ĭ��45
		float mFarDist;
		float mNearDist;

		float mAspect;//��߱���

		Vector3f mPosition;//λ��
		Vector3f mLookPosition;//����λ��
		Vector3f mDirection;//����
		Vector3f mUP;//�Ϸ���

		Vector3f mCameraRightDirection;//�ҷ���
		Vector3f mCameraUpDirection;//��������Ϸ���

	private:
		bool mIsUpdateCamera;
		Matrix4f mCameraViewMat;
		Matrix4f mCameraPerspective;
	};
}
