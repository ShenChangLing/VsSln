#pragma once
#include "SCLPrerequisites.h"
#include "SCLResource.h"

namespace SCL
{
	
	class SCL_DLL Mesh :public Resource
	{
	public:
		Mesh(const String& name,const String& group);
		~Mesh();
	};


}