#include <curl/curl.h>
#include <stdexcept>
#include "transport.hpp"

namespace Transport
{
	TransportImpl::TransportImpl(const Setting::Settings& settings)
		: settings_(settings)
	{
	}
	
	TransportImpl(TransportImpl&& other)
	{
		curl_ = other.curl_;
        that.curl_ = nullptr;
	}
	
	TransportImpl& TransportImpl::operator=(const TransportImpl&& other)
	{
		std::swap(curl_, other.curl_);
		return *this;
	}
	
	TransportImpl::~TransportImpl()
	{
		if(curl_ != nullptr)
		{
			/* always cleanup */ 
			curl_easy_cleanup(curl_);
			curl_ = nullptr;
		}
	}
	
	size_t writeCallback(char* contents, size_t size, size_t nmemb, std::string* buffer)
	{
		size_t realsize = size * nmemb;
		if(buffer == NULL)
		{
			return 0;
		}
		buffer->append(contents, realsize);
		return realsize;  
	}

	void TransportImpl::initialise()
	{
		curl_ = curl_easy_init();
		if ( curl_ == nullptr )
		{
			throw std::logic_error("curl_ not initialise.");
		}
		
		curl_easy_setopt(curl_, CURLOPT_URL, settings_.getConnection());
		// example.com is redirected, so we tell libcurl to follow redirection
		curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);
		
		curl_easy_setopt(curl_, CURLOPT_VERBOSE, 0);
		curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(curl_, CURLOPT_USERAGENT, "Validator/1.0");
		curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &writeCallback);
		curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &buffer_);
		
		/* Perform the request, res will get the return code */ 
		CURLcode res = curl_easy_perform(curl_);
		/* Check for errors */ 
		if(res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				  curl_easy_strerror(res));
		}
	 
	}
	
	std::string TransportImpl::getWhiteList(const std::string& query) const
	{
		if(curl_)
		{
			curl_easy_setopt(curl_, CURLOPT_URL, settings_.getConnection());
			// perform transfer
			CURLcode code = curl_easy_perform(curl_);
			// check if everything went fine
			if(code == CURLE_OK)
			{
				return std::move(buffer_);
			}
			// clear the buffer
			//buffer.clear();
		}
		return std::string();
	}

}