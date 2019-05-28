#pragma once
#include "SCLPrerequisites.h"
#include "SCLSingleton.h"

namespace SCL
{
	class NetworkManager : public Singleton<NetworkManager>
	{
		struct NetworkManagerData;
	public:
		NetworkManager();
		~NetworkManager();

		void networkThread();//网络的请求执行部分在线程中

		//处理HTTP请求
		void perform(HttpRequest* http_request);

	private:
		void _addToThread(HttpRequest* http_request);//增加到线程中

	protected:
		NetworkManagerData *mNetworkManagerData;

		typedef std::deque<HttpRequest*> HttpRequestDeque;
		HttpRequestDeque mHttpRequests;//HTTP请求队列

		SCL_AUTO_MUTEX;
	};
}