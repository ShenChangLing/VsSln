#include "SCLPrerequisites.h"
#include "SCLNetworkManager.h"
#include "SCLInteriorHeader.h"

namespace SCL
{
	NetworkManager::NetworkManager()
	{
		curl_global_init(CURL_GLOBAL_DEFAULT);
	}

	NetworkManager::~NetworkManager()
	{
		curl_global_cleanup();
	}


}
