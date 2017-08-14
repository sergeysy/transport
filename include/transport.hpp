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
	//TransportImpl();
    explicit TransportImpl(const Setting::Settings& settings);
    /*{
        std::swap(curl_, other.curl_);
        std::swap(settings_, other.settings_);
        return *this;
    };*/
	~TransportImpl();
    TransportImpl( TransportImpl&& other) = delete;
    /*{
        std::swap(curl_, other.curl_);
        //std::swap(settings_, other.settings_);
        settings_ = other.settings_;
        other.curl_ = nullptr;
        other.settings_ = Setting::Settings();
    }*/

    //TransportImpl(TransportImpl&);
    TransportImpl& operator=( TransportImpl&&) = delete;
	
	void initialise();
	std::string getWhiteList(const std::string& query);
	
private:
    Setting::Settings settings_;
	CURL *curl_ = nullptr;
	std::string buffer_;

	// disable copy, assign. enable only move
	TransportImpl(const TransportImpl&) = delete;
	TransportImpl& operator=(const TransportImpl&) = delete;
};
}
