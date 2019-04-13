#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	class SCL_DLL Resource
	{
	public:
		Resource(const String& name, const String& groupName);
		virtual ~Resource();

		const String& getGroupName() const { return mGroupName; }
		const String& getName() const { return mName; }

	protected:
		String mName;
		String mGroupName;
	};
}
