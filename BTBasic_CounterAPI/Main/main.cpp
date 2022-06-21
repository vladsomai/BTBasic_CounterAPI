#include "../Headers/lib.h"
#include "../Headers/TCPDatabaseConnection.h"
#include "../Headers/XDevDatabaseConnection.h"
#include "../Headers/DatabaseHandler.h"
#include "../Headers/BTBasic_Wrapper_DLL.h"

using namespace TCPDatabaseConnectionNS;
using namespace XDevDatabaseConnectionNS;
using namespace DatabaseHandlerNS;

extern EXT_DLL_Result BTBasic_DLL_Call(char* functionName, char* parameters,
	char* returnString, int* returnValue);

int main()
{
	{
		char function[]{ "Connect" };
		char parameters[]{ "TCP,35.198.72.42,root,3ng1n33r" };
		char buffer[2000]{};
		int* retVal{ nullptr };

		BTBasic_DLL_Call(function, parameters, buffer, retVal);
		std::cout << buffer << std::endl;
	}

	{
		char function[]{ "IncrementCounter" };
		char parameters[]{ "104,FCT" };
		char buffer[2000]{};
		int* retVal{ nullptr };

		BTBasic_DLL_Call(function, parameters, buffer, retVal);
		std::cout << buffer << std::endl;
	}

	{
		char function[]{ "UpdateTemperature" };
		char parameters[]{ "104,FCT,23" };
		char buffer[2000]{};
		int* retVal{ nullptr };

		BTBasic_DLL_Call(function, parameters, buffer, retVal);
		std::cout << buffer << std::endl;
	}

	{
		char function[]{ "UpdateContacts" };
		char parameters[]{ "104,FCT,80001" };
		char buffer[2000]{};
		int* retVal{ nullptr };

		BTBasic_DLL_Call(function, parameters, buffer, retVal);
		std::cout << buffer << std::endl;
	}

	{
		char function[]{ "UpdateContacts" };
		char parameters[]{ "105,FCT,80001" };
		char buffer[2000]{};
		int* retVal{ nullptr };

		BTBasic_DLL_Call(function, parameters, buffer, retVal);
		std::cout << buffer << std::endl;
	}

	{
		char function[]{ "Disconnect" };
		char parameters[]{ "" };
		char buffer[2000]{};
		int* retVal{ nullptr };
		BTBasic_DLL_Call(function, parameters, buffer, retVal);
		std::cout << buffer << std::endl;
	}

	/*
	//DatabaseHandler
	{
		std::unique_ptr<DatabaseHandler> TCPconnection = std::make_unique<DatabaseHandler>();
		std::string result = TCPconnection->Connect(DatabaseConnectionTypes::TCP, "35.198.72.42", "root", "3ng1n33r");
		std::cout << result << std::endl;
	}

	*/
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
	*/

}