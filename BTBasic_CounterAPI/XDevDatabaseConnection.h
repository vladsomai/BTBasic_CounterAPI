#pragma once
#ifndef XDevDatabaseConnectionH
#define XDevDatabaseConnectionH
#include "lib.h"

class XDevDatabaseConnection {
private:
    std::shared_ptr<mysqlx::Session> session{ nullptr };
    std::shared_ptr<mysqlx::Schema> schema{nullptr};
    std::shared_ptr<mysqlx::Table> table{ nullptr };

public:
    XDevDatabaseConnection() = default;
    ~XDevDatabaseConnection() { if(session) session->close(); };

    std::string Connect(std::string DBURL);
    std::string IncrementCounter(std::string AdapterCode, std::string AdapterType);
    std::string UpdateStationTemperature(std::string AdapterCode, std::string AdapterType, std::string Temperature);
};

#endif XDevDatabaseConnectionH