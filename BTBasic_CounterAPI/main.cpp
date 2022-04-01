#include "lib.h"

std::string (incrementCounter)(std::string DBURL,
                               std::string adapter_code,
                               std::string fixture_type);
int main()
{
	std::string DBURL = "mysqlx://root:3ng1n33r@tm-fixture-counter";
	std::string adapter_code = "1706";
	std::string fixture_type = "ICT";

	std::string result = incrementCounter(DBURL, adapter_code, fixture_type);
	if (result == "OK")
	{
		std::cout<<"Adapter code incremented!"<<std::endl;
	}
	else
	{
		std::cout << result << std::endl;
	}
}