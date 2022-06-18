#include "../Headers/lib.h"
#include "../Headers/TCPDatabaseConnection.h"
#include "../Headers/XDevDatabaseConnection.h"

int main()
{
	//Using TCP
	{
		std::unique_ptr<TCPDatabaseConnection> TCPconnection = std::make_unique<TCPDatabaseConnection>();
		std::string connectionResult = TCPconnection->Connect("35.198.72.42", "root", "3ng1n33r");
		std::cout << connectionResult << std::endl;
		if (connectionResult != "Connected!")
			return 0;

		//increment counter
		{
			std::string result = TCPconnection->IncrementCounter("104", "FCT");
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
			std::string result = TCPconnection->UpdateStationTemperature("104", "FCT","21");
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

	//Using XDevAPI
	{
		std::unique_ptr<XDevDatabaseConnection> XDevConnection = std::make_unique<XDevDatabaseConnection>();
		std::string connectionResult = XDevConnection->Connect("mysqlx://root:3ng1n33r@127.0.0.1");
		std::cout << connectionResult << std::endl;
		if (connectionResult != "Connected!")
			return 0;

		//increment counter
		{
			std::string result = XDevConnection->IncrementCounter("104", "FCT");
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
			std::string result = XDevConnection->UpdateStationTemperature("102", "FCT","22");
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
}