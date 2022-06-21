#include "../Headers/DatabaseHandler.h"
#include "../Headers/TCPDatabaseConnection.h"
#include "../Headers/XDevDatabaseConnection.h"

namespace DatabaseHandlerNS
{
	using namespace TCPDatabaseConnectionNS;
	using namespace XDevDatabaseConnectionNS;

	std::string DatabaseHandler::Connect(DatabaseConnectionTypes ConnectionType, std::string Host, std::string User, std::string Password)
	{
		this->ConnectionType = ConnectionType;

		if (ConnectionType == DatabaseConnectionTypes::TCP)
		{
			this->DatabaseConnection = std::make_unique<TCPDatabaseConnection>();
		}
		else if (ConnectionType == DatabaseConnectionTypes::XDevAPI)
		{
			this->DatabaseConnection = std::make_unique<XDevDatabaseConnection>();
		}
		else
			throw "Invalid request";

		std::string connectionResult = this->DatabaseConnection->Connect(Host, User, Password);
		return connectionResult;
	}

	std::string DatabaseHandler::MakeDatabaseAction(DatabaseActionTypes Action, std::string AdapterCode, std::string AdapterType, std::optional<std::string> Temperature, std::optional<std::string> Contacts)
	{
		std::string result{ "Invalid request" };
		switch (Action)
		{
		case DatabaseHandlerNS::DatabaseActionTypes::IncrementCounter:
			result = this->DatabaseConnection->IncrementCounter(AdapterCode, AdapterType);
			break;
		case DatabaseHandlerNS::DatabaseActionTypes::UpdateTemperature:
			if (Temperature != std::nullopt)
				result = this->DatabaseConnection->UpdateStationTemperature(AdapterCode, AdapterType, Temperature.value());
			else
				result = "You requested to update the temperature but did not provide a value!";
			break;
		case DatabaseHandlerNS::DatabaseActionTypes::UpdateContacts:
			if (Contacts != std::nullopt)
				result = this->DatabaseConnection->UpdateContacts(AdapterCode, AdapterType, Contacts.value());
			else
				result = "You requested to update the contacts but did not provide a value!";
			break;
		default:
			break;
		}

		return result;
	}
}