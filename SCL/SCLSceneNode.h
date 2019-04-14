#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	// 场景中用于显示的场景节点
	class SCL_DLL SceneNode
	{
	public:
		SceneNode(Scene* scene);
		~SceneNode();

	protected:
		Scene* mScene;
	};
}
