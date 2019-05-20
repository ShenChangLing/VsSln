#include "SCLPrerequisites.h"
#include "SCLHttpRequest.h"

namespace SCL
{
	HttpRequest::HttpRequest()
	{
		mType = HttpRequest::UNKNOWN;
		mURL = "";
		mSSLCAFilename = "";
	}

	HttpRequest::~HttpRequest()
	{
		mType = HttpRequest::UNKNOWN;
		mURL.clear();
		mSSLCAFilename.clear();
	}

	HttpRequest * HttpRequest::clone()
	{
		HttpRequest* request = new HttpRequest();
		request->setType(this->getType()).
		setURL(this->getURL()).
		setSSLCAFilename(this->getSSLCAFilename().c_str());
		return request;
	}
}