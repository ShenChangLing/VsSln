#include "SCLPrerequisites.h"
#include "SCLResourceManager.h"
#include "SCLResource.h"

namespace SCL
{
	

	ResourceManager::ResourceManager()
	{
	}


	ResourceManager::~ResourceManager()
	{
	}

	ResourcePtr ResourceManager::createResource(const String & name, const String & groupName)
	{
		Resource* resource = _createImpl(name, groupName);
		ResourcePtr ret(resource);

		addImpl(ret);

		return ret;
	}

	void ResourceManager::addImpl(ResourcePtr & ptr)
	{
		SCL_AUTO_LOCK_MUTEX;
		auto iter = mResourceGroups.find(ptr->getGroupName());
		if (iter == mResourceGroups.end())
		{
			ResourceList reslist;
			mResourceGroups.insert(ResourceGroupList::value_type(ptr->getGroupName(), reslist));
			iter = mResourceGroups.find(ptr->getGroupName());
		}
		iter->second.insert(ResourceList::value_type(ptr->getName(), ptr));
	}

	void ResourceManager::removeImpl(const ResourcePtr & ptr)
	{
		SCL_AUTO_LOCK_MUTEX;
		auto iter = mResourceGroups.find(ptr->getGroupName());
		if (iter != mResourceGroups.end())
		{
			auto iter1 = iter->second.find(ptr->getName());
			if (iter1!=iter->second.end())
			{
				iter->second.erase(iter1);
			}
			if (iter->second.empty())
			{
				mResourceGroups.erase(iter);
			}
		}
	}

}