#include "TCPDatabaseConnection.h"

using std::cout;
using std::endl;

std::string TCPDatabaseConnection::Connect(const std::string Host, const std::string User, const std::string Password)
{
    std::string returnString = "Connected!";

    sql::ConnectOptionsMap connection_properties;

    connection_properties["hostName"] = "tcp://" + Host;
    connection_properties["userName"] = User;
    connection_properties["password"] = Password;
    connection_properties["schema"] = "counterdb";
    connection_properties["port"] = 3306;
    connection_properties["OPT_RECONNECT"] = true;
    connection_properties["OPT_CONNECT_TIMEOUT"] = 5;

    try
    {
        connnection.reset(MySQLInstance.connect(connection_properties));
        statement.reset(connnection->createStatement());
        statement->execute("use counterdb;");
    }
    catch (const sql::SQLException& exp)
    {
        if (exp.getErrorCode() != 0)
        {
            returnString = exp.what();
        }
    }

    return returnString;
}

std::string TCPDatabaseConnection::UpdateStationTemperature(const std::string AdapterCode, const std::string AdapterType, const std::string Temperature) {

    std::string returnString = "OK";

    try {
        result.reset(statement->executeQuery("call updateTemperature(" + AdapterCode + "," + "\"" + AdapterType + "\"" + +"," + Temperature + ");"));
    }
    catch (const sql::SQLException& exp)
    {
        if (exp.getErrorCode() != 0)
        {
            returnString = exp.what();
        }
    }
    return returnString;
}

std::string TCPDatabaseConnection::IncrementCounter(const std::string AdapterCode, const std::string AdapterType)
{
    std::string returnString = "OK";
    try 
    {
        result.reset(statement->executeQuery("call incrementCounter(" + AdapterCode + "," + "\"" + AdapterType + "\"" + ");"));
    }
    catch (const sql::SQLException& exp)
    {
        if (exp.getErrorCode() != 0)
        {
            returnString = exp.what();
        }
    }
    return returnString;
}