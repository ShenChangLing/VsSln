#include "SCLPrerequisites.h"
#include "SCLHttpResponse.h"

namespace SCL
{
	HttpResponse::HttpResponse(HttpRequest* http_request)
		:mHttpRequest(http_request)
	{
		mResponseData.clear();
	}

	HttpResponse::~HttpResponse()
	{
		mResponseData.clear();
	}

	void HttpResponse::_addResponseData(const char * data, size_t size)
	{
		(void)size;
		mResponseData += data;
	}
}