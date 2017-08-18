#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <curl/curl.h>

#include "settings.hpp"
#include "transport.hpp"
#include "logger.hpp"

namespace Transport
{
	/*TransportImpl::TransportImpl()
	    :curl_(nullptr)
	{
	}*/

    TransportImpl::TransportImpl(const Setting::Settings& settings)
        : settings_(settings)
	{
        curl_global_init(CURL_GLOBAL_DEFAULT);
	}
	
    /*TransportImpl& TransportImpl::operator=(TransportImpl&& other)
	{
	    std::swap(curl_, other.curl_);
	    std::swap(settings_, other.settings_);
	    return *this;
    }*/
	
	TransportImpl::~TransportImpl()
	{
        curl_global_cleanup();
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
/*
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
}*/

    std::string TransportImpl::getHttp(const std::string& query)
    {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        CURL *curl_ = nullptr;
        curl_ = curl_easy_init();
        std::string result;
        if(curl_)
        {
            //curl_easy_setopt(curl_, CURLOPT_URL, settings_.getConnection());
            const auto request = settings_.getConnection()+query;
            std::cerr<< logger() <<"URL:\""<< request <<"\""<<std::endl;
            curl_easy_setopt(curl_, CURLOPT_URL, request.c_str());
            struct curl_slist *chunk = NULL;
            chunk = curl_slist_append(chunk, "Accept: application/json");
            curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, chunk);

            curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &writeCallback);
            std::string localBuffer;
            curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &localBuffer);
            /*
             * WARNING WE DISABLE SSL VERIFY CERTIFICATE
            */
            curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);
            /*
             * WARNING END
            */

            // perform transfer
            CURLcode code = curl_easy_perform(curl_);
            // check if everything went fine
            if(code == CURLE_OK)
            {
                std::cerr<< logger() <<localBuffer.size()<<" bytes return request \""<< request <<"\":"<<std::endl<<localBuffer<<std::endl;
                result = std::move(localBuffer);
            }
            else
            {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                      curl_easy_strerror(code));
            }
            curl_easy_cleanup(curl_);
        }
        else
        {
            std::cerr<< logger() <<"curl not initialised!";
        }
        curl_global_cleanup();

        return result;
    }

    std::string TransportImpl::postHttp(const std::string& query)
    {
        CURL *curl_ = nullptr;

        std::string result;
        curl_ = curl_easy_init();
        if(curl_)
        {
            //curl_easy_setopt(curl_, CURLOPT_URL, settings_.getConnection());
            const auto request = settings_.getConnection()+"/transactions";
            std::cerr << logger() <<"URL:\""<< request << "\" POST: \"" <<query << "\"" <<std::endl;
            curl_easy_setopt(curl_, CURLOPT_URL, request.c_str());
            struct curl_slist *chunk = NULL;
            chunk = curl_slist_append(chunk, "Accept: */*");
            chunk = curl_slist_append(chunk, "application/x-www-form-urlencoded");
            curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, chunk);

            curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &writeCallback);
            std::string localBuffer;
            curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &localBuffer);
            /*
             * WARNING WE DISABLE SSL VERIFY CERTIFICATE
            */
            curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);
            /*
             * WARNING END
            */

            curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, query.c_str());
            curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, query.size());
            curl_easy_setopt(curl_, CURLOPT_POST, 1L);
            curl_easy_setopt(curl_, CURLOPT_TIMEOUT, 100);
            // perform transfer
            CURLcode code = curl_easy_perform(curl_);
            // check if everything went fine
            if(code == CURLE_OK)
            {
                std::cerr<< logger() <<localBuffer.size()<<" bytes return request \""<< request <<"\":"<<std::endl<<localBuffer<<std::endl;
                result = std::move(localBuffer);
                //return std::move(localBuffer);
            }
            else
            {
                // clear the buffer
                //buffer.clear();
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                      curl_easy_strerror(code));
                //return std::string();
            }
            curl_easy_cleanup(curl_);
        }
        else
        {
            std::cerr<< logger() <<"curl not initialised!";
            //return std::string();
        }

        return result;
    }
}
