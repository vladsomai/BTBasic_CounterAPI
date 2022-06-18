#include "../Headers/XDevDatabaseConnection.h"

using std::cout;
using std::endl;

std::string XDevDatabaseConnection::Connect(const std::string DBURL)
{
    std::string returnString = "Connected!";

    try
    {
        session.reset(new mysqlx::Session(DBURL));
        schema.reset(new mysqlx::Schema(session->getSchema("counterdb")));
        table.reset(new mysqlx::Table(schema->getTable("Projects")));
       
        session->sql("use counterdb;").execute();
    }
    catch (const mysqlx::Error& err)
    {
        return err.what();
    }

    return returnString;
}
std::string XDevDatabaseConnection::UpdateStationTemperature(const std::string AdapterCode, const std::string AdapterType, const std::string Temperature) {

    std::string returnString = "OK";

    try {
        session->sql("call updateTemperature(" + AdapterCode + "," + "\"" + AdapterType + "\"" + +"," + Temperature + ");").execute();
    }
    catch (const mysqlx::Error& err)
    {
        return err.what();
    }

    return returnString;
}

std::string XDevDatabaseConnection::IncrementCounter(const std::string AdapterCode, const std::string AdapterType)
{
    std::string returnString = "OK";
    try
    {
        session->sql("call incrementCounter(" + AdapterCode + "," + "\"" + AdapterType + "\"" + ");").execute();
    }
    catch (const mysqlx::Error& err)
    {
        return err.what();
    }

    return returnString;
}
