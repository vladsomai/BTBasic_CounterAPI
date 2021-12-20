#include "lib.h"

using std::cout;
using std::endl;
using namespace ::mysqlx;

const char *(incrementCounter)(std::string DBURL, std::string adapter_code, std::string fixture_type)
{
    try
    {
        Session sess(DBURL);

        Schema sch = sess.getSchema("counterdb");
        Table table = sch.getTable("projects");

        sess.sql("use counterdb;").execute();
        sess.sql("call incrementCounter(" + adapter_code + "," + "\"" + fixture_type + "\"" + ")").execute();
        sess.close();
    }
    catch (const mysqlx::Error &err)
    {
        return err.what();
    }
    catch (std::exception &ex)
    {
#if _DEBUG
        cout << "STD EXCEPTION: " << ex.what() << endl;
#endif
        return ex.what();
    }
    catch (const char *ex)
    {
#if _DEBUG
        cout << "EXCEPTION: " << ex << endl;
#endif

        return ex;
    }

    return "OK";
    
}