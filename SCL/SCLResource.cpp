#include "SCLPrerequisites.h"
#include "SCLResource.h"

namespace SCL
{
	Resource::Resource(const String& name, const String& groupName)
		: mName(name), mGroupName(groupName)
	{
	}

	Resource::~Resource()
	{
	}
}