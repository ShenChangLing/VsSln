#pragma once
#include "SCLSingleton.h"

namespace SCL
{
	class NetworkManager : public Singleton<NetworkManager>
	{
		struct NetworkManagerData;
	public:
		NetworkManager();
		~NetworkManager();

		void networkThread();

	protected:
		NetworkManagerData *mNetworkManagerData;
	};
}