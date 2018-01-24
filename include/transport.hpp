#pragma once

#include <string>
#include <utility>

#include <boost/thread/recursive_mutex.hpp>

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

    void initialise();
    std::string getHttp(const std::string& service, const std::string& query);
    std::string postTsvHttp(const std::string& service, const std::string& query);
    std::string postJsonHttp(const std::string& service, const std::string& query);

    StatusTransport::EnumType getLastStatus() const;
    std::pair<size_t,size_t> getStatus() const;

private:
    // disable copy, assign. move
    TransportImpl( TransportImpl&& other) = delete;
    TransportImpl& operator=( TransportImpl&&) = delete;
    TransportImpl(const TransportImpl&) = delete;
    TransportImpl& operator=(const TransportImpl&) = delete;

    StatusTransport::EnumType lastStatus_;
    void setStatuses(const StatusTransport::EnumType& status);
    size_t countGoodStatus_=0;
    size_t countFailStatus_=0;

    mutable boost::recursive_mutex  eventsMutex_;
};

}
