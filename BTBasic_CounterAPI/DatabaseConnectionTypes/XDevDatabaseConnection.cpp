#include "../Headers/XDevDatabaseConnection.h"

namespace XDevDatabaseConnectionNS
{
    using std::cout;
    using std::endl;

    std::string XDevDatabaseConnection::Connect(const std::string Host, const std::string User, const std::string Password)
    {
        std::string returnString = "Connected!";
        std::string DBURL{ "mysqlx://" + User + ":" + Password + "@" + Host };

        try
        {
            session = std::make_unique<mysqlx::Session>(DBURL);
            schema = std::make_unique<mysqlx::Schema>(session->getSchema("counterdb"));
            table = std::make_unique<mysqlx::Table>(schema->getTable("Projects"));
            
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

    std::string XDevDatabaseConnection::UpdateContacts(const std::string AdapterCode, const std::string AdapterType, const std::string Contacts)
    {
        std::string returnString = "OK";
        try
        {
            session->sql("call updateContacts(" + AdapterCode + "," + "\"" + AdapterType + "\"" + "," + Contacts + ");").execute();
        }
        catch (const mysqlx::Error& err)
        {
            return err.what();
        }

        return returnString;
    }
}