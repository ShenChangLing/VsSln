#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	class SCL_DLL Renderer
	{
	public:
		enum CLEAR_BUFFER_BIT
		{
			CBB_Color = 1,
			CBB_Depth = 1 << 1,
			CBB_Stencil = 1 << 2,
		};
	public:
		Renderer();
		~Renderer();

		void attachRenderTarget(RenderTarget& rt); //����Ⱦ
		RenderTarget* detachRenderTarget(const String& name); //������ȾĿ��

		void updateAllRenderTargets();

		void setViewport(Viewport* viewport); //���õ�ǰ�ӿ�
		void setRenderTarget(RenderTarget* rt);

		void clear(CLEAR_BUFFER_BIT bit,const ColorValue& color);

	public:
		typedef std::multimap<uchar, RenderTarget*> PrioritisedRenderTarget;
		typedef std::unordered_map<RenderTarget*, RendererStateCache*> RendererStateCaches;
	private:
		PrioritisedRenderTarget mPrioritisedRenderTargets; //���ȼ��Ĵ��ڣ����ȼ��ߵ��Ȼ���

		RendererStateCaches mRenderStateCaches;
		RendererStateCache* mCurrentRenderStateCache;

		RenderTarget* mCurrentRenderTarget;
		Viewport* mCurrentViewport;
	};
}
