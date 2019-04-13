#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{

	template<typename T>
	class SCL_DLL Singleton
	{
	public:
		~Singleton()
		{
			assert(mSingleton);
			mSingleton = nullptr;
		}

		static T* getSingletonPtr() { assert(mSingleton); return mSingleton; }
		static T& getSingleton() { assert(mSingleton); return *mSingleton; }
	protected:
		Singleton()
		{
			assert(!mSingleton);
			mSingleton = static_cast<T*>(this);
		}
	private:
		Singleton(const Singleton<T>&) = delete;
		Singleton& operator=(const Singleton<T>&) = delete;
	protected:
		static T																						*mSingleton;
	};

}
