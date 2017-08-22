#pragma once

#include <string>

#include <curl/curl.h>

namespace Transport
{
class TransportImpl
{
public:
	//TransportImpl();
    explicit TransportImpl();

	~TransportImpl();
    TransportImpl( TransportImpl&& other) = delete;
    TransportImpl& operator=( TransportImpl&&) = delete;
	
	void initialise();
    std::string getHttp(const std::string& service, const std::string& query);
    std::string postHttp(const std::string& service, const std::string& query);

private:
    // disable copy, assign. enable only move
	TransportImpl(const TransportImpl&) = delete;
	TransportImpl& operator=(const TransportImpl&) = delete;
};
}
