#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <curl/curl.h>

#include "transport.hpp"
#include "logger.hpp"

namespace Transport
{
    TransportImpl::TransportImpl()
	{
        curl_global_init(CURL_GLOBAL_DEFAULT);
	}
	
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
	}
class CURL_Wrapper
{
    CURL *curl_;
    std::string localBuffer_;
    std::string request_;
public:
    CURL_Wrapper()
        :curl_(curl_easy_init())
    {
        if(curl_ == nullptr)
        {
            throw std::logic_error("curl not initialised!");
        }

        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &writeCallback);

        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &localBuffer_);

        /*
         * WARNING WE DISABLE SSL VERIFY CERTIFICATE
        */
        curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);
        /*
         * WARNING END
        */

    }

    void setUrl(const std::string& request)
    {
        request_ = request;
        curl_easy_setopt(curl_, CURLOPT_URL, request.c_str());
    }

    std::string execute()
    {
        // perform transfer
        CURLcode curl_code = curl_easy_perform(curl_);

        if(curl_code == CURLE_OK)
        {
            std::cerr<< logger() <<localBuffer_.size()<<" bytes return request \""<< request_ <<"\":"<<std::endl<<localBuffer_<<std::endl;
            long http_code = 0;
            curl_easy_getinfo (curl_, CURLINFO_RESPONSE_CODE, &http_code);
            std::cerr << logger() << "http code: " << http_code << std::endl;
            if (http_code == 200 && curl_code != CURLE_ABORTED_BY_CALLBACK)
            {
                //Succeeded
                return std::move(localBuffer_);
            }
            else
            {
                 //Failed
                throw std::logic_error("Http code: "+ std::to_string(http_code));
            }
        }
        else
        {
            throw std::logic_error(std::string("curl_easy_perform() failed: ") + curl_easy_strerror(curl_code));
        }
    }

    ~CURL_Wrapper()
    {
        std::cerr << logger() << __PRETTY_FUNCTION__ << std::endl;
        curl_easy_cleanup(curl_);
    }

    operator CURL*() const { return curl_; }
    operator CURL*&(){ return curl_; }
};
    std::string TransportImpl::getHttp(const std::string& service, const std::string& query)
    {
        CURL_Wrapper curl_;
        std::string result;
        const auto request = service+query;
        std::cerr<< logger() <<"URL:\""<< request <<"\""<<std::endl;
        curl_.setUrl(request);
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, "Accept: application/json");
        curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, chunk);


        result = curl_.execute();

        return result;
    }

    std::string TransportImpl::postHttp(const std::string& service, const std::string& query)
    {
        CURL_Wrapper curl_;

        std::string result;

        const auto request = service;
        std::cerr << logger() <<"URL:\""<< request << "\" POST: \"" <<query << "\"" <<std::endl;
        curl_.setUrl(request);
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, "Accept: */*");
        chunk = curl_slist_append(chunk, "application/x-www-form-urlencoded");
        curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, chunk);

        curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, query.c_str());
        curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, query.size());
        curl_easy_setopt(curl_, CURLOPT_POST, 1L);
        curl_easy_setopt(curl_, CURLOPT_TIMEOUT, 100);
        // perform transfer
        result = curl_.execute();

        return result;
    }
}
