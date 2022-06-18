#pragma once

#ifndef TCPDatabaseConnectionH
#define TCPDatabaseConnectionH
#include "lib.h"

class TCPDatabaseConnection {
private:
    sql::mysql::MySQL_Driver MySQLInstance{};
    std::shared_ptr <sql::Connection> connnection{ nullptr };
    std::shared_ptr <sql::Statement> statement{ nullptr };
    std::shared_ptr <sql::ResultSet> result{ nullptr };

public:
    TCPDatabaseConnection() = default;
    ~TCPDatabaseConnection() = default;

    std::string Connect(std::string Host, std::string User, std::string Password);
    std::string IncrementCounter(std::string AdapterCode, std::string AdapterType);
    std::string UpdateStationTemperature(std::string AdapterCode, std::string AdapterType, std::string Temperature);
};

#endif TCPDatabaseConnectionH