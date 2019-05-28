#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	class SCL_DLL HttpResponse
	{
		friend static size_t curl_writefun_callback(char* data, size_t n, size_t l, void *userp);
	public:
		HttpResponse(HttpRequest* http_request);
		~HttpResponse();

		const String getResponseData() const { return mResponseData.c_str(); }

	public:
	protected:
		//增加响应数据，内部使用,外部不要调用
		void _addResponseData(const char* data, size_t size);

	private:
		String mResponseData;//响应的数据
		HttpRequest* mHttpRequest;//响应请求
	};
}
