#pragma once

#include <string>

#include <curl/curl.h>

#include "enumdefinition.inl"

DECLARE_ENUM_4(StatusTransport,
               OK, L"Coonection good",
               Fail, L"Fail",
               FailConnect, L"Fail connect",
               FailAnswer, L"Fail answer"
               );
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

    StatusTransport::EnumType getLastStatus() const;

private:
    // disable copy, assign. enable only move
	TransportImpl(const TransportImpl&) = delete;
	TransportImpl& operator=(const TransportImpl&) = delete;

    StatusTransport::EnumType lastStatus_;
};

}
