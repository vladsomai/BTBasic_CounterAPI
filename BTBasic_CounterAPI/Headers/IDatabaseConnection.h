#pragma once
#ifndef IDatabaseConnectionH
#define IDatabaseConnectionH
#include "lib.h"

namespace IDatabaseConnectionNS
{
    class IDatabaseConnection {

    public:
        virtual ~IDatabaseConnection() = default;

        virtual std::string Connect(std::string Host, std::string User, std::string Password) = 0;
        virtual std::string IncrementCounter(std::string AdapterCode, std::string AdapterType) = 0;
        virtual std::string UpdateStationTemperature(std::string AdapterCode, std::string AdapterType, std::string Temperature) = 0;
        virtual std::string UpdateContacts(std::string AdapterCode, std::string AdapterType, std::string Contacts) = 0;
    };
}
#endif IDatabaseConnectionH