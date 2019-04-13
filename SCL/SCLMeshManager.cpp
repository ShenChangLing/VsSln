#include "SCLPrerequisites.h"
#include "SCLMeshManager.h"

template<> SCL::MeshManager* SCL::Singleton<SCL::MeshManager>::mSingleton = nullptr;

namespace SCL
{
		
	MeshManager::MeshManager()
	{
	}


	MeshManager::~MeshManager()
	{
	}

	Resource * MeshManager::_createImpl(const String & name, const String & groupName)
	{
		return nullptr;
	}

}
