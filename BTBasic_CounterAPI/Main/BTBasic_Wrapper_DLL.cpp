/*
* !!!READ ME!!!!
* 
* DLL MUST BE COMPILED ON X86 ONLY.
* 
* YOU CAN USE GLOBAL VARIABLES - THEY WILL EXIST BETWEEN "dllload" and "dllunload" calls from BTBasic testplan.
* 
* YOU CANNOT DEREFERENCE THE "returnValue" PARAMETER, IT IS SET ONLY BY THE BTBasic HOST PROCESS WITH THE ENUM RETURN TYPE.
* The "returnValue" can be used from HOSTS only.
*
* DEFAULT "returnValue" FROM "BTBasic_DLL_Call" function is "EXT_DLL_Result::EXT_DLL_Result_Error", 
* RETRUN "EXT_DLL_Result::EXT_DLL_Result_OK" ONLY WHEN YOUR CONDITIONS ARE MET.
* 
* YOU CAN RETURN INFO TO BTBasic TESTPLAN ONLY WITH "returnString", MAXIMUM 2048 BYTES.
* 
* DO NOT CHANGE THE "BTBasic_DLL_Call" FUNCTION SIGNATURE OR REDEFINE / MODIFY THE ENUM "EXT_DLL_Result" FROM THE HEADER.
* 
*/
#include "../Headers/lib.h"
#include "../Headers/BTBasic_Wrapper_DLL.h"
#include "../Headers/DatabaseHandler.h"

using namespace DatabaseHandlerNS;

extern void copyReturnString(const char* input, char* retString);
extern std::vector<std::string> parse_C_style_str(char* input);


static std::unique_ptr<DatabaseHandler> DatabaseConnection{ nullptr };

DllExport EXT_DLL_Result BTBasic_DLL_Call(char* functionName, char* parameters,
	char* returnString, int* returnValue)
{
	const char* messageToReturn = nullptr;
	size_t sizeOfMessage{};
	std::string result = "";

	std::vector<std::string> params = parse_C_style_str(parameters);

	//Handle each function here
	if (strcmp(functionName, "IncrementCounter") == 0)
	{
		if (DatabaseConnection == nullptr)
		{
			copyReturnString("ERROR: Please connect to the database first using the Connect function!", returnString);
			return EXT_DLL_Result::EXT_DLL_Result_Error;
		}

		std::string AdapterCode{};
		std::string AdapterType{};

		try
		{
			AdapterCode = params.at(0);
			AdapterType = params.at(1);
		}
		catch (const std::out_of_range&)
		{
			copyReturnString("ERROR: Invalid parameters, please provide adapter code and fixture type!", returnString);
			return EXT_DLL_Result::EXT_DLL_Result_Error;
		}
		
		result = DatabaseConnection->MakeDatabaseAction(DatabaseActionTypes::IncrementCounter, AdapterCode, AdapterType, std::nullopt, std::nullopt);

		if (result =="OK")
		{
			copyReturnString("SUCCESS: Adapter code incremented!", returnString);
			return EXT_DLL_Result::EXT_DLL_Result_OK;
		}
		else
		{
			copyReturnString(result.c_str(), returnString);
			return EXT_DLL_Result::EXT_DLL_Result_Error;
		}
	}
	else if (strcmp(functionName, "UpdateTemperature") == 0)
	{
		if (DatabaseConnection == nullptr)
		{
			copyReturnString("ERROR: Please connect to the database first using the Connect function!", returnString);
			return EXT_DLL_Result::EXT_DLL_Result_Error;
		}

		std::string AdapterCode{};
		std::string AdapterType{};
		std::string Temperature{};

		try
		{
			AdapterCode = params.at(0);
			AdapterType = params.at(1);
			Temperature = params.at(2);
		}
		catch (const std::out_of_range&)
		{
			copyReturnString("ERROR: Invalid parameters, please provide adapter code, fixture type and temperature!", returnString);
			return EXT_DLL_Result::EXT_DLL_Result_Error;
		}

		result = DatabaseConnection->MakeDatabaseAction(DatabaseActionTypes::UpdateTemperature, AdapterCode, AdapterType, Temperature, std::nullopt);

		if (result == "OK")
		{
			copyReturnString("SUCCESS: Station temperature set!", returnString);
			return EXT_DLL_Result::EXT_DLL_Result_OK;
		}
		else
		{
			copyReturnString(result.c_str(), returnString);
			return EXT_DLL_Result::EXT_DLL_Result_Error;
		}
	}
	else if (strcmp(functionName, "UpdateContacts") == 0)
	{
		if (DatabaseConnection == nullptr)
		{
			copyReturnString("ERROR: Please connect to the database first using the \"Connect\" function!", returnString);
			return EXT_DLL_Result::EXT_DLL_Result_Error;
		}

		std::string AdapterCode{};
		std::string AdapterType{};
		std::string Contacts{};

		try
		{
			AdapterCode = params.at(0);
			AdapterType = params.at(1);
			Contacts = params.at(2);
		}
		catch (const std::out_of_range&)
		{
			copyReturnString("ERROR: Invalid parameters, please provide adapter code, fixture type and temperature!", returnString);
			return EXT_DLL_Result::EXT_DLL_Result_Error;
		}

		result = DatabaseConnection->MakeDatabaseAction(DatabaseActionTypes::UpdateContacts, AdapterCode, AdapterType, std::nullopt, Contacts);

		if (result == "OK")
		{
			copyReturnString("SUCCESS: Adapter's contacts are updated!", returnString);
			return EXT_DLL_Result::EXT_DLL_Result_OK;
		}
		else
		{
			copyReturnString(result.c_str(), returnString);
			return EXT_DLL_Result::EXT_DLL_Result_Error;
		}
	}	
	else if (strcmp(functionName, "Connect") == 0)
	{

		std::string ConnectionTypeString{};
		DatabaseConnectionTypes ConnectionType{};
		std::string Host{};
		std::string User{};
		std::string Password{};

		try
		{
			ConnectionTypeString = params.at(0);
			Host = params.at(1);
			User = params.at(2);
			Password = params.at(3);
		}
		catch (const std::out_of_range&)
		{
			copyReturnString("ERROR: Invalid parameters, please provide the following(in same order): 1.DB connection type(TCP/XDev), 2.Host(IP/DNS), 3.DB User, 4.DB Password!", returnString);
			return EXT_DLL_Result::EXT_DLL_Result_Error;
		}

		if (ConnectionTypeString == "TCP")
			ConnectionType = DatabaseConnectionTypes::TCP;
		else if (ConnectionTypeString == "XDev")
			ConnectionType = DatabaseConnectionTypes::XDevAPI;
		else
		{
			copyReturnString("ERROR: Invalid parameters, please provide a valid DB Connection type(TCP/XDev)!", returnString);
			return EXT_DLL_Result::EXT_DLL_Result_Error;
		}

		if (DatabaseConnection == nullptr)
		{
			DatabaseConnection = std::make_unique<DatabaseHandler>();
		}

		if (DatabaseConnection != nullptr)
			result = DatabaseConnection->Connect(ConnectionType, Host, User, Password);
		else
			result = "Database connection is not valid!";

		if (result == "Connected!")
		{
			copyReturnString("SUCCESS: Connected to database!", returnString);
			return EXT_DLL_Result::EXT_DLL_Result_OK;
		}
		else
		{
			copyReturnString(result.c_str(), returnString);
			return EXT_DLL_Result::EXT_DLL_Result_Error;
		}
	}
	else if (strcmp(functionName, "Disconnect") == 0)
	{
		if (DatabaseConnection != nullptr)
		{

			DatabaseConnection.reset(nullptr);
			copyReturnString("SUCCESS: Disconnected from database!", returnString);
			return EXT_DLL_Result::EXT_DLL_Result_OK;
		}
		else
		{
			copyReturnString("Database connection was not valid, disconnecting is irrelevant.", returnString);
			return EXT_DLL_Result::EXT_DLL_Result_Error;
		}
	}
	else
	{
		copyReturnString("Function does not exist!", returnString);
		return EXT_DLL_Result::EXT_DLL_Result_Error;
	}

	/*
	* DO NOT REMOVE
	* Function should not reach this state
	* Secure the return of the function in case programmer messes with the if block above
	*/
	copyReturnString("Default return state reached, please chack the wrapper DLL return paths", returnString);
	return EXT_DLL_Result::EXT_DLL_Result_Error;
}

