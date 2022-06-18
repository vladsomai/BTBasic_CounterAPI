#include "lib.h"
#include "TCPDatabaseConnection.h"
#include "XDevDatabaseConnection.h"

int main()
{
/*
	//Using TCP
	{
		std::unique_ptr<TCPDatabaseConnection> TCPconnection = std::make_unique<TCPDatabaseConnection>();
		std::string connectionResult = TCPconnection->Connect("35.198.72.42", "root", "3ng1n33r");
		std::cout << connectionResult << std::endl;
		if (connectionResult != "Connected!")
			return 0;

		//increment counter
		{
			std::string result = TCPconnection->IncrementCounter("104", "FT");
			if (result == "OK")
			{
				std::cout << "Adapter code incremented!" << std::endl;
			}
			else
			{
				std::cout << result << std::endl;
			}
		}	
		
		//update temperature
		{
			std::string result = TCPconnection->UpdateStationTemperature("104", "FC","21");
			if (result == "OK")
			{
				std::cout << "Station temperature set!" << std::endl;
			}
			else
			{
				std::cout << result << std::endl;
			}
		}
	}
	*/

	//Using XDevAPI
	{
		std::unique_ptr<XDevDatabaseConnection> XDevConnection = std::make_unique<XDevDatabaseConnection>();
		std::string connectionResult = XDevConnection->Connect("mysqlx://root:3ng1n33r@192.168.1.10");
		std::cout << connectionResult << std::endl;
		if (connectionResult != "Connected!")
			return 0;

			return 0;
		std::string adapter_code = "1706";
		std::string fixture_type = "ICT";

		//std::string result = XDevConnection->IncrementCounter("104", "FC");
		std::string result = "OK";
		if (result == "OK")
		{
			std::cout << "Adapter code incremented!" << std::endl;
		}
		else
		{
			std::cout << result << std::endl;
		}
	}
}