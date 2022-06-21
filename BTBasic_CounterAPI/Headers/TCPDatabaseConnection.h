#pragma once
#ifndef TCPDatabaseConnectionH
#define TCPDatabaseConnectionH
#include "lib.h"
#include "IDatabaseConnection.h"

namespace TCPDatabaseConnectionNS
{
    using namespace IDatabaseConnectionNS;

    class TCPDatabaseConnection :public IDatabaseConnection {
    private:
        sql::Driver* Driver{ nullptr }; //do not free this pointer -> C++ connector does it by itself.
        std::unique_ptr<sql::Connection> connnection{ nullptr };
        std::unique_ptr<sql::Statement> statement{ nullptr };
        std::unique_ptr<sql::ResultSet> result{ nullptr };

    public:
        TCPDatabaseConnection() { Driver = sql::mysql::get_driver_instance(); };
        ~TCPDatabaseConnection() = default;

        std::string Connect(std::string Host, std::string User, std::string Password) override;
        std::string IncrementCounter(std::string AdapterCode, std::string AdapterType) override;
        std::string UpdateStationTemperature(std::string AdapterCode, std::string AdapterType, std::string Temperature) override;
        std::string UpdateContacts(std::string AdapterCode, std::string AdapterType, std::string Contacts) override;
    };
}
#endif TCPDatabaseConnectionH