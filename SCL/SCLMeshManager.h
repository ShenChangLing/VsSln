#pragma once
#include "SCLPrerequisites.h"
#include "SCLSingleton.h"
#include "SCLResourceManager.h"

namespace SCL
{
		
	class SCL_DLL MeshManager :public ResourceManager, public Singleton<MeshManager>
	{
	public:
		MeshManager();
		~MeshManager();

		MeshPtr load(const String& fileName,const String& groupName);

	protected:
		virtual Resource* _createImpl(const String& name, const String& groupName) override;

	private:
		typedef std::unordered_map<String, Mesh*> MeshList;
	};


}
