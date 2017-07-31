#pragma once

#include "settings.hpp"

namespace Transport
{
class TransportImpl
{
public:
	explicit TransportImpl(const Setting::Settings& settings);
	~TransportImpl();
	TransportImpl(const TransportImpl&& other);
	TransportImpl& operator=(const TransportImpl&&);
	
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