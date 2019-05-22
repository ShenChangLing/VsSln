#include "SCLPrerequisites.h"
#include "SCLNetworkManager.h"
#include "SCLHttpRequest.h"
#include "SCLInteriorHeader.h"

template<> SCL::NetworkManager * SCL::Singleton<SCL::NetworkManager>::mSingleton = nullptr;

namespace SCL
{
	namespace Thread
	{
		static bool networkExit = false;//退出当前你网络线程
		static int networkMaxConnects = 10;//最大的网络链接个数

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
		mHttpRequests.clear();

		mNetworkManagerData = new NetworkManagerData();
		Thread::startThread(this);
	}

	NetworkManager::~NetworkManager()
	{
		Thread::quitThread();

		delete mNetworkManagerData;
		mNetworkManagerData = nullptr;

		mHttpRequests.clear();
	}

	void NetworkManager::networkThread()
	{
		int running_handles = 1;
		unsigned int link_count = 0;

		int msgs_in_queue = -1;
		CURLMsg *curl_msg;

		//启用最大的同时网络连接数
		curl_multi_setopt(mNetworkManagerData->curlm, CURLMOPT_MAXCONNECTS, Thread::networkMaxConnects);

		do
		{
			{//如果有需要加入到队列中的请加入
				SCL_AUTO_LOCK_MUTEX;
				while (!mHttpRequests.empty())
				{
					_addToThread(mHttpRequests.front());
					mHttpRequests.pop_front();//从头删除
				}
			}

			//执行网络请求
			curl_multi_perform(mNetworkManagerData->curlm, &running_handles);

			//读取链接信息
			while ((curl_msg = curl_multi_info_read(mNetworkManagerData->curlm, &msgs_in_queue)))
			{
				if (curl_msg->msg == CURLMSG_DONE)
				{
					//链接完成,移除当前的链接信息
					CURL* e_handle = curl_msg->easy_handle;

					if (curl_msg->data.result != CURLcode::CURLE_OK)
					{
						SCL_DLOGINFO << curl_msg->data.result << curl_easy_strerror(curl_msg->data.result);
					}
					else
					{//成功处理就通知监听对象，我处理请求完成了
						
					}
					curl_multi_remove_handle(mNetworkManagerData->curlm, e_handle);
					curl_easy_cleanup(e_handle);
				}
				else
				{
					SCL_DLOGINFO << "当前CURL消息类型为：" + curl_msg->msg;
				}
			}

			//等待一会继续处理当前程序
			if (running_handles)
			{
				curl_multi_wait(mNetworkManagerData->curlm, nullptr, 0, 1000, nullptr);
			}
			else if (mHttpRequests.empty())
			{
				//休闲当前线程
				std::unique_lock<std::mutex> lock(Thread::mutex);
				Thread::condition_variable.wait(lock);
			}
		} while (!Thread::networkExit);//线程不需要推出

		SCL_DLOGINFO << "结束网络连接线程";
	}

	void NetworkManager::perform(HttpRequest * http_request)
	{
		SCL_AUTO_LOCK_MUTEX;

		mHttpRequests.push_back(http_request);
		//唤醒线程
		Thread::condition_variable.notify_one();
	}
	static size_t temp(char* data, size_t n, size_t l, void *userp)
	{
		HttpRequest *request = static_cast<HttpRequest*>(userp);
		SCL_DLOGINFO << data;
		return n * l;
	}
	void NetworkManager::_addToThread(HttpRequest* http_request)
	{
		CURL *curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, http_request->getURL());

		if (http_request->getType() == HttpRequest::POST)
		{
			curl_easy_setopt(curl, CURLOPT_POST, 1L);//启用POST
		}
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, temp);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, http_request);

		if (http_request->getSSLCAFilename().empty())
		{
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);//不启用CA证书
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		}
		else
		{
			curl_easy_setopt(curl, CURLOPT_CAPATH, http_request->getSSLCAFilename());
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);//启用CA证书
		}

		curl_multi_add_handle(mNetworkManagerData->curlm, curl);
	}
}