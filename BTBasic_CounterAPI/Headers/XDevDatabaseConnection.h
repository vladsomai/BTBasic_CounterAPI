#pragma once
#ifndef XDevDatabaseConnectionH
#define XDevDatabaseConnectionH
#include "lib.h"
#include "../Headers/IDatabaseConnection.h"

namespace XDevDatabaseConnectionNS
{
    using namespace IDatabaseConnectionNS;

    class XDevDatabaseConnection :public IDatabaseConnection{
    private:
        std::unique_ptr<mysqlx::Session> session{ nullptr };
        std::unique_ptr<mysqlx::Schema> schema{ nullptr };
        std::unique_ptr<mysqlx::Table> table{ nullptr };

    public:
        XDevDatabaseConnection() = default;
        ~XDevDatabaseConnection() { if (session) session->close(); };

        std::string Connect(std::string Host, std::string User, std::string Password) override;
        std::string IncrementCounter(std::string AdapterCode, std::string AdapterType) override;
        std::string UpdateStationTemperature(std::string AdapterCode, std::string AdapterType, std::string Temperature) override;
        std::string UpdateContacts(std::string AdapterCode, std::string AdapterType, std::string Contacts) override;
    };
}
#endif XDevDatabaseConnectionH