#include "lib.h"

const char* (incrementCounter)(std::string DBURL,
	std::string adapter_code,
	std::string fixture_type);
int main()
{
	std::string DBURL = "mysqlx://root:3ng1n33r@127.0.0.1";
	std::string adapter_code = "1714";
	std::string fixture_type = "ICT";

	const char* result = incrementCounter(DBURL, adapter_code, fixture_type);
	if (strcmp(result, "OK") == 0)
	{
		std::cout<<"Adapter code incremented!"<<std::endl;
	}
	else
	{
		std::cout << result << std::endl;
	}
}