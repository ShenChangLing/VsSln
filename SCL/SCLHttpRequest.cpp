#include "SCLPrerequisites.h"
#include "SCLHttpRequest.h"
#include "SCLHttpResponse.h"

namespace SCL
{
	HttpRequest::HttpRequest()
	{
		mType = HttpRequest::UNKNOWN;
		mURL = "";
		mSSLCAFilename = "";

		mListeners.clear();
		mResponse = new HttpResponse(this);

		mRequestHeaderMap.clear();
	}

	HttpRequest::~HttpRequest()
	{
		SCL_AUTO_LOCK_MUTEX;

		mType = HttpRequest::UNKNOWN;
		mURL.clear();
		mSSLCAFilename.clear();

		delete mResponse;
		mResponse = nullptr;

		mRequestHeaderMap.clear();
	}

	HttpRequest * HttpRequest::clone()
	{
		HttpRequest* request = new HttpRequest();

		SCL_AUTO_LOCK_MUTEX;

		request->setType(this->getType()).
			setURL(this->getURL()).
			setRequestHeaders(this->getRequestHeaders()).
			setSSLCAFilename(this->getSSLCAFilename().c_str());
		return request;
	}

	void HttpRequest::addListener(Listener * listener)
	{
		SCL_AUTO_LOCK_MUTEX;

		ListenerList::iterator iter = std::find(mListeners.begin(), mListeners.end(), listener);
		if (iter == mListeners.end())
		{
			//没有存在在添加有了就不添加
			mListeners.push_back(listener);
		}
	}

	void HttpRequest::removeListener(Listener * listener)
	{
		SCL_AUTO_LOCK_MUTEX;

		ListenerList::iterator iter = std::find(mListeners.begin(), mListeners.end(), listener);
		if (iter != mListeners.end())
		{
			//没有存在在添加有了就不添加
			mListeners.erase(iter);
		}
	}

	void HttpRequest::removeListeners()
	{
		SCL_AUTO_LOCK_MUTEX;
		mListeners.clear();
	}

	const char* HttpRequest::getHeader(const char* type) const
	{
		auto iter = mRequestHeaderMap.find(type);
		if (iter == mRequestHeaderMap.end())
			return nullptr;
		else
			return iter->second.c_str();
	}

	void HttpRequest::_notificationRequestFinal()
	{
		SCL_AUTO_LOCK_MUTEX;

		for (auto listener : mListeners)
		{
			listener->requestFinal(this, mResponse);
		}
	}
}