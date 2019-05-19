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
		inline void setType(Type type) { mType = type; }

		inline const char* getURL() const { return mURL.c_str(); }
		inline void setURL(const char* url) { mURL = url; }

	private:
		Type mType;
		String mURL;
	};
}
