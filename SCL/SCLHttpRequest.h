#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	class SCL_DLL HttpRequest
	{
		friend class NetworkManager;
	public:
		//HTTP请求类型
		enum Type
		{
			GET,
			POST,
			PUT,
			UNKNOWN,//未知类型
		};

		//HTTP请求监听对象
		class Listener
		{
		public:
			//返回true表示监听不在继续传递
			virtual  bool requestFinal(HttpRequest* request, HttpResponse* response) = 0;//请求完成
		};

	public:
		HttpRequest();
		~HttpRequest();

		inline const Type getType() const { return mType; }
		inline HttpRequest& setType(Type type)
		{
			mType = type;
			return *this;
		}

		inline const char* getURL() const { return mURL.c_str(); }
		inline HttpRequest& setURL(const char* url)
		{
			mURL = url;
			return  *this;
		}

		HttpRequest& setSSLCAFilename(const char* caFilename)
		{
			mSSLCAFilename = caFilename;
			return *this;
		}
		const String& getSSLCAFilename()const { return mSSLCAFilename; }

		/**
		 * \brief 返回一个和当前请求一致的新对象,需要在不用的时候手动delete
		 * \return HttpRequest 新的HTTP请求对象
		 */
		HttpRequest* clone();

		HttpResponse* getHttpResponse() { return mResponse; }

		void addListener(Listener* listener);
		void removeListener(Listener* listener);
		void removeListeners();

	public:///请求头系列函数接口

		typedef  std::unordered_map<String, String> RequestHeaderMap;

		const RequestHeaderMap& getRequestHeaders() const { return mRequestHeaderMap; }
		HttpRequest& setRequestHeaders(const RequestHeaderMap& headers)
		{
			mRequestHeaderMap = headers;
			return *this;
		}

		//可接受的内容类型
		HttpRequest& setHeaderOfAccept(const char* Accept)
		{
			mRequestHeaderMap["Accept"] = Accept;
			return *this;
		}
		const char* getHeaderOfAccept() const
		{
			return getHeader("Accept");
		}

		//链接类型
		HttpRequest& setHeaderOfConnection(const char* Connection)
		{
			mRequestHeaderMap["Connection"] = Connection;
			return *this;
		}
		const char* getHeaderOfConnection() const
		{
			return getHeader("Connection");
		}

		const char* getHeader(const char* type) const;
	protected:
		//通知监听对象完成请求
		void _notificationRequestFinal();
	private:
		Type mType;
		String mURL;

		/**
		 * \brief SSL证书路径文件,默认路径为"",表示不存在证书
		 */
		String mSSLCAFilename;//

		HttpResponse* mResponse;//HTTP响应

		typedef  std::list<Listener*> ListenerList;
		ListenerList mListeners;//监听对象列表

		RequestHeaderMap mRequestHeaderMap;//请求头集合

		SCL_AUTO_MUTEX;//互斥对象
	};
}
