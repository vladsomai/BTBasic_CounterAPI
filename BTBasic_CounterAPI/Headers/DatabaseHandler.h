#pragma once
#include "../Headers/lib.h"
#include "../Headers/TCPDatabaseConnection.h"
#include "../Headers/XDevDatabaseConnection.h"
#include "../Headers/IDatabaseConnection.h"
#include <optional>

namespace DatabaseHandlerNS
{
	enum class DatabaseConnectionTypes { TCP, XDevAPI };
	enum class DatabaseActionTypes { IncrementCounter, UpdateTemperature, UpdateContacts };
	
	using namespace IDatabaseConnectionNS;

	class DatabaseHandler
	{
	private:
		DatabaseConnectionTypes ConnectionType{};
		std::unique_ptr<IDatabaseConnection> DatabaseConnection{nullptr};

	public:
		DatabaseHandler() = default;
		~DatabaseHandler() = default;
		
		std::string Connect(DatabaseConnectionTypes ConnectionType, std::string Host, std::string User, std::string Password);
		std::string MakeDatabaseAction(DatabaseActionTypes Action, std::string AdapterCode, std::string AdapterType, std::optional<std::string> Temperature, std::optional<std::string> Contacts);
	};
}