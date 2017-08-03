#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <curl/curl.h>

#include "settings.hpp"
#include "transport.hpp"

namespace Transport
{
	/*TransportImpl::TransportImpl()
	    :curl_(nullptr)
	{
	}*/

	TransportImpl::TransportImpl(const Setting::Settings& settings)
		: settings_(std::move(settings))
	{
	}
	
	TransportImpl& TransportImpl::operator=(TransportImpl&& other)
	{
	    std::swap(curl_, other.curl_);
	    std::swap(settings_, other.settings_);
	    return *this;
	}
	
	TransportImpl::~TransportImpl()
	{
		if(curl_ != nullptr)
		{
			// always cleanup
			curl_easy_cleanup(curl_);
			curl_ = nullptr;
			std::cout<<__FUNCTION__<<". Clear curl success."<<std::endl;
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
		/*curl_ = curl_easy_init();
		if ( curl_ == nullptr )
		{
			throw std::logic_error("curl_ not initialise.");
		}
		*/
		//curl_easy_setopt(curl_, CURLOPT_URL, settings_.getConnection());
		/*curl_easy_setopt(curl_, CURLOPT_URL,
		    settings_.getConnection() + "/checkreg?phoneNumber=0079165364242");
		// example.com is redirected, so we tell libcurl to follow redirection
		curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);
		
		curl_easy_setopt(curl_, CURLOPT_VERBOSE, 0);
		curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(curl_, CURLOPT_USERAGENT, "Validator/1.0");
		curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &writeCallback);
		curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &buffer_);
		*/
		/* Perform the request, res will get the return code */ 
		/*CURLcode res = curl_easy_perform(curl_);
		// Check for errors
		if(res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				  curl_easy_strerror(res));
		}*/
	 
	}

static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp)
{
    if(userp)
    {
	std::ostream& os = *static_cast<std::ostream*>(userp);
	std::streamsize len = size * nmemb;
	if(os.write(static_cast<char*>(buf), len))
	    return len;
    }

    return 0;
}

CURLcode curl_read(const std::string& url, std::ostream& os, long timeout = 30)
{
    CURLcode code(CURLE_FAILED_INIT);
    CURL* curl = curl_easy_init();

    if(curl)
    {
	if(CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write))
	&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L))
	&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L))
	//&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FILE, &os))
	&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout))
	&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, url.c_str())))
	{
	    struct curl_slist *chunk = NULL;
	    chunk = curl_slist_append(chunk, "Accept: application/json");
	    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

	    code = curl_easy_perform(curl);
	}
	curl_easy_cleanup(curl);
    }
    return code;
}

	std::string TransportImpl::getWhiteList(const std::string& query)
	{
		curl_global_init(CURL_GLOBAL_DEFAULT);

		curl_ = curl_easy_init();
		if(curl_)
		{
			//curl_easy_setopt(curl_, CURLOPT_URL, settings_.getConnection());
		//const auto request
		std::cerr<<"URL:\""<<settings_.getConnection()<<query<<"\""<<std::endl;
		curl_easy_setopt(curl_, CURLOPT_URL,
		    (settings_.getConnection()
		    +query).c_str()
		    );
		struct curl_slist *chunk = NULL;
		chunk = curl_slist_append(chunk, "Accept: application/json");
		curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, chunk);

		curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &writeCallback);
		curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &buffer_);
		
			// perform transfer
			CURLcode code = curl_easy_perform(curl_);
			// check if everything went fine
			if(code == CURLE_OK)
			{
				std::cerr<<buffer_.size()<<" bytes return request:"<<std::endl<<buffer_<<std::endl;
				return std::move(buffer_);
			}
			// clear the buffer
			//buffer.clear();
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				  curl_easy_strerror(code));
		    curl_easy_cleanup(curl_);
			return std::string();
		}
		else
		{
		    std::cerr<<"curl not initialised!";
		    return std::string();
		}
		curl_global_cleanup();

	    /*curl_global_init(CURL_GLOBAL_ALL);
	    std::ostringstream oss;
std::cerr<<settings_.getConnection()<<query<<" kjhkjhkjh"<<std::endl;
	    CURLcode code = curl_read(settings_.getConnection()+query, oss);
	    if(CURLE_OK == code)
	    {
		// Web page successfully written to string
		std::string html = oss.str();
		std::cerr<<html.size()<<" bytes."<<html;
	    }
	    else
	    {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(code));
	    }
	    curl_global_cleanup();
	    return std::string();*/
	}

}