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

		void attachRenderTarget(RenderTarget& rt); //绑定渲染
		RenderTarget* detachRenderTarget(const String& name); //分离渲染目标

		void updateAllRenderTargets();

		void setViewport(Viewport* viewport); //设置当前视口
		void setRenderTarget(RenderTarget* rt);

		void clear(CLEAR_BUFFER_BIT bit,const ColorValue& color);

	public:
		typedef std::multimap<uchar, RenderTarget*> PrioritisedRenderTarget;
		typedef std::unordered_map<RenderTarget*, RendererStateCache*> RendererStateCaches;
	private:
		PrioritisedRenderTarget mPrioritisedRenderTargets; //优先级的窗口，优先级高的先绘制

		RendererStateCaches mRenderStateCaches;
		RendererStateCache* mCurrentRenderStateCache;

		RenderTarget* mCurrentRenderTarget;
		Viewport* mCurrentViewport;
	};
}
