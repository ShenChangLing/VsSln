#pragma once

namespace SCL
{
	class HttpRequest
	{
	public:
		//HTTP请求类型
		enum Type
		{
			GET,
			POST,
			PUT,
			UNKNOWN,//未知类型
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
	private:
		Type mType;
		String mURL;

		/**
		 * \brief SSL证书路径文件,默认路径为"",表示不存在证书
		 */
		String mSSLCAFilename;//
	};
}
