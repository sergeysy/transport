#pragma once

#include <string>

#include <curl/curl.h>

namespace Setting
{
    class Settings;
}

namespace Transport
{
class TransportImpl
{
public:
	TransportImpl();
	explicit TransportImpl(const Setting::Settings& settings);
	~TransportImpl();
	TransportImpl(TransportImpl&& other);
	TransportImpl& operator=( TransportImpl&&);
	
	void initialise();
	std::string getWhiteList(const std::string& query) const;
	
private:
	Setting::Settings settings_;
	CURL *curl_ = nullptr;
	std::string buffer_;

	// disable copy, assign. enable only move
	TransportImpl(const TransportImpl&) = delete;
	TransportImpl& operator=(const TransportImpl&) = delete;
};
}