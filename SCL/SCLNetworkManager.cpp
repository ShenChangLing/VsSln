#include "SCLPrerequisites.h"
#include "SCLNetworkManager.h"
#include "SCLInteriorHeader.h"

template<> SCL::NetworkManager * SCL::Singleton<SCL::NetworkManager>::mSingleton = nullptr;

namespace SCL
{
	namespace Thread
	{
		static bool networkExit = false;//退出当前你网络线程

		static std::mutex mutex;//线程互斥对象
		static std::condition_variable condition_variable;//等待线程唤醒

		void startThread(NetworkManager* nm)
		{
			SCL_DLOGINFO << "启动网络连接线程";

			std::thread * networkThread = nullptr;
			networkThread = new std::thread(&NetworkManager::networkThread, nm);
			networkThread->detach();

			delete networkThread;
			networkThread = nullptr;

			SCL_DLOGINFO << "结束网络连接线程";
		}

		void quitThread()
		{
			networkExit = true;
			condition_variable.notify_one();
		}
	}

	struct NetworkManager::NetworkManagerData
	{
		CURLM* curlm;

		NetworkManagerData()
		{
			memset(this, 0, sizeof(NetworkManagerData));

			curl_global_init(CURL_GLOBAL_DEFAULT);
			curlm = curl_multi_init();
		}

		~NetworkManagerData()
		{
			curl_multi_cleanup(curlm);
			curlm = nullptr;

			curl_global_cleanup();
		}
	};

	NetworkManager::NetworkManager()
	{
		mNetworkManagerData = new NetworkManagerData();
		Thread::startThread(this);
	}

	NetworkManager::~NetworkManager()
	{
		Thread::quitThread();

		delete mNetworkManagerData;
		mNetworkManagerData = nullptr;
	}

	void NetworkManager::networkThread()
	{
		int running_handles = 1;
		unsigned int link_count = 0;

		int msgs_in_queue = -1;
		CURLMsg *curl_msg;

		while (!Thread::networkExit)
		{
			do
			{
				curl_multi_perform(mNetworkManagerData->curlm, &running_handles);

			//读取链接信息
			while ((curl_msg = curl_multi_info_read(mNetworkManagerData->curlm, &msgs_in_queue)))
			{
				if (curl_msg->msg == CURLMSG_DONE)
				{
					//链接完成,移除当前的链接信息
				}
				else
				{
					SCL_DLOGINFO << "当前CURL消息类型为："+curl_msg->msg;
				}
			}
				if (running_handles)
				{
					curl_multi_wait(mNetworkManagerData->curlm, nullptr, 0, 1000, nullptr);
				}
			} while (running_handles);

			std::unique_lock<std::mutex> lock(Thread::mutex);
			Thread::condition_variable.wait(lock);
		}
	}
}