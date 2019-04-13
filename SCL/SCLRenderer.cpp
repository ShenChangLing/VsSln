#include "SCLPrerequisites.h"
#include "SCLRenderer.h"
#include "SCLRenderTarget.h"
#include "SCLRendererStateCache.h"
#include "SCLViewport.h"
#include "SCLCamera.h"
#include "SCLInteriorHeader.h"
#include "SCLColorValue.h"

namespace SCL
{
	Renderer::Renderer()
	{
		mPrioritisedRenderTargets.clear();

		mRenderStateCaches.clear();
		mCurrentRenderStateCache = nullptr;
		mCurrentRenderTarget = nullptr;
		mCurrentViewport = nullptr;
	}


	Renderer::~Renderer()
	{
		mPrioritisedRenderTargets.clear();
		mCurrentRenderStateCache = nullptr;
		mCurrentRenderTarget = nullptr;
		mCurrentViewport = nullptr;

		for (auto i : mRenderStateCaches)
		{
			delete i.second;
		}
		mRenderStateCaches.clear();
	}

	void Renderer::attachRenderTarget(RenderTarget& rt)
	{
		for (auto i : mPrioritisedRenderTargets)
		{
			if (i.second == &rt)
				return;
		}

		mPrioritisedRenderTargets.insert(PrioritisedRenderTarget::value_type(rt.getPrioritised(), &rt));
	}

	RenderTarget* Renderer::detachRenderTarget(const String& name)
	{
		PrioritisedRenderTarget::iterator iter, iterend;
		iter = mPrioritisedRenderTargets.begin();
		iterend = mPrioritisedRenderTargets.end();

		for (; iter != iterend; ++iter)
		{
			if ((iter->second)->getName() == name)
			{
				iter = mPrioritisedRenderTargets.erase(iter);
				break;
			}
		}
		return nullptr;
	}

	void Renderer::updateAllRenderTargets()
	{
		for (auto i : mPrioritisedRenderTargets)
		{
			(i.second)->update();
		}
	}

	void Renderer::setViewport(Viewport* viewport)
	{
		if (viewport == nullptr)
		{
			setRenderTarget(nullptr);
		}
		else if (viewport != mCurrentViewport)
		{
			//��ǰ���ӿں��Ѿ�������ӿ���ͬһ���Ͳ�����
			auto rt = viewport->getRenderTarget();

			setRenderTarget(rt);

			mCurrentViewport = viewport;

			int x = 0, y = 0, w = 0, h = 0;
			viewport->getActualDimensions(x, y, w, h);

			mCurrentRenderStateCache->setViewport(x, y, w, h);
		}
	}

	void Renderer::setRenderTarget(RenderTarget* rt)
	{
		if (rt == mCurrentRenderTarget)
			return;

		if (rt == nullptr)
		{
			mCurrentRenderTarget->unbindCurrentContext(); //���ǰ����
			mCurrentRenderTarget = rt;
			return;
		}

		mCurrentRenderTarget = rt;

		//�󶨵���ǰ������
		mCurrentRenderTarget->bindCurrentContext();

		//�ҵ�Ŀ��Ķ�Ӧ��Ⱦ״̬����
		auto iter = mRenderStateCaches.find(rt);
		if (iter == mRenderStateCaches.end())
		{
			//û���ҵ��ʹ�������һ��
			mCurrentRenderStateCache = new RendererStateCache();
			mRenderStateCaches.insert(RendererStateCaches::value_type(mCurrentRenderTarget, mCurrentRenderStateCache));
		}
		else
		{
			mCurrentRenderStateCache = iter->second;
		}
	}

	void Renderer::clear(CLEAR_BUFFER_BIT bit, const ColorValue & color)
	{
		uint clearBit = 0;
		if (bit & CBB_Color)
		{
			mCurrentRenderStateCache->setClearColor(color);
			clearBit |= GL_COLOR_BUFFER_BIT;
		}

		glClear(clearBit);
	}

}
