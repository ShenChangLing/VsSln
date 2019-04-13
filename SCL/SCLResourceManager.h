#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	
	class SCL_DLL ResourceManager
	{
	public:
		ResourceManager();
		virtual ~ResourceManager();

		ResourcePtr createResource(const String& name, const String& groupName);

	protected:
		virtual Resource* _createImpl(const String& name, const String& groupName) = 0;
		void addImpl(ResourcePtr& ptr);
		void removeImpl(const ResourcePtr& ptr);

	protected:
		typedef std::unordered_map<String, ResourcePtr> ResourceList;
		typedef std::unordered_map<String, ResourceList> ResourceGroupList;

	protected:
		SCL_AUTO_MUTEX;

		ResourceGroupList mResourceGroups;
	};

}
