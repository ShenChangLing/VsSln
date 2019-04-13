#pragma once
#include "SCLPrerequisites.h"
#include "SCLColorValue.h"

namespace SCL
{
	class Viewport
	{
	public:
		Viewport(Camera* camera, RenderTarget* rt, float left = 0.0f, float top = 0.0f, float width = 1.0f,
		         float height = 1.0f);
		~Viewport();

		void update();
		void clear(uint clearMask);

		RenderTarget* getRenderTarget() { return mRenderTarget; }

		void getActualDimensions(int &left, int& top, int& width, int& height) const;

		const ColorValue& getBackgroundColorValue() const { return mBackgroundColorValue; }

	protected:
		void _updateDimensions();//������ʵ���ӿ�����

	protected:
		Camera* mCamera;
		RenderTarget* mRenderTarget;

		//�ӿڵ�������,�ϱߣ���ȣ��߶ȷ�Χ��0-1��
		float mRelativeLeft;
		float mRelativeTop;
		float mRelativeWidth;
		float mRelativeHeight;

		//�ӿڵ���ʵ��ߣ��ϱߣ���ȣ��߶�(��Ļ����)
		int mActualLeft;
		int mActualTop;
		int mActualWidth;
		int mActualHeight;

		ColorValue mBackgroundColorValue;
	};
}
