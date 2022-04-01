#include "lib.h"

using std::cout;
using std::endl;
using namespace ::mysqlx;

std::string incrementCounter(std::string DBURL, 
                             std::string adapter_code, 
                             std::string fixture_type)
{

    std::string returnString{"OK"};
    try
    {
        Session sess(DBURL);

        Schema sch = sess.getSchema("counterdb");
        Table table = sch.getTable("Projects");

        sess.sql("use counterdb;").execute();
        sess.sql("call incrementCounter(" + adapter_code + "," + "\"" + fixture_type + "\"" + ")").execute();
        sess.close();
    }
    catch (const mysqlx::Error &err)
    {

#if _DEBUG
        cout << "ERROR EXCEPTION: " << err.what() << endl;
#endif
        returnString = err.what();
    }
    catch (std::exception &ex)
    {
#if _DEBUG
        cout << "STD EXCEPTION: " << ex.what() << endl;
#endif
        returnString = ex.what();
    }
    catch (const char *ex)
    {
#if _DEBUG
        cout << "EXCEPTION: " << ex << endl;
#endif

        returnString = ex;
    }

    return returnString;
}