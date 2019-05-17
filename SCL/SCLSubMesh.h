#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	class SCL_DLL SubMesh
	{
	public:
		SubMesh(Mesh* mesh);
		~SubMesh();

		Mesh* getParentMesh() const { return mParentMesh; }
	private:
		Mesh* mParentMesh;//父模型
	};
}
