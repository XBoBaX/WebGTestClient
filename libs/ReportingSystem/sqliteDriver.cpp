#include "sqliteDriver.h"

namespace reportS {

	SqliteDriver::SqliteDriver()
	{
		CreateDB();
		CrateTable();
	}

	void SqliteDriver::InsertData() 
	{
		char* messageError;

		int exit = sqlite3_open(cNameSqlBase, &DB);

		std::string sql = "INSERT INTO COLLECTIONS (TESTCASE, STATUS, TYPETEST, TIMEMS, COUNTREQ) VALUES ('','','',0,0);";

		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) 
		{
			std::cerr << "Error Insert\n";
			sqlite3_free(messageError);
		}
		else
		{
			std::cout << "Records created Successfully";
		}
	}

	void SqliteDriver::CreateDB()
	{
		int exit = 0;
		exit = sqlite3_open(cNameSqlBase, &DB);
		if (exit) {
			std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		}
		else
			std::cout << "Opened Database Successfully!" << std::endl;
		sqlite3_close(DB);
	}

	void SqliteDriver::CrateTable()
	{
		std::string sql = "CREATE TABLE IF NOT EXISTS COLLECTIONS("
			"ID INTEGER PRIMARY KEY AUTOINCRIMENT,"
			"TESTCASE	TEXT NOT NULL,"
			"STATUS		TEXT NOT NULL,"
			"TYPETEST	TEXT NOT NULL,"
			"TIMEMS		INT NOT NULL,"
			"COUNTREQ	INT NOT NULL);";
		try
		{
			int exit = 0;
			exit = sqlite3_open(cNameSqlBase, &DB);

			char* messageError;
			exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

			if (exit != SQLITE_OK) 
			{
				std::cerr << "Error Create Table\n";
				sqlite3_free(messageError);
			}
			else
			{
				std::cout << "Table created Successfully\n";
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what();
		}
	}
}