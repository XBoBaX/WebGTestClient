#include "sqliteDriver.h"

namespace reportS {

	SqliteDriver::SqliteDriver()
	{
		CreateDB();

		std::string sql = "CREATE TABLE IF NOT EXISTS COLLECTIONS("
			"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"TESTCASE	TEXT NOT NULL,"
			"STATUS		TEXT NOT NULL,"
			"TYPETEST	TEXT NOT NULL,"
			"TIMEMS		INT NOT NULL,"
			"COUNTREQ	INT NOT NULL);";
		CrateTable(sql);

		sql = "CREATE TABLE IF NOT EXISTS REPORTS("
			"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"NAMETEST	TEXT NOT NULL,"
			"CLASSNAME	TEXT NOT NULL,"
			"RESULT		TEXT NOT NULL,"
			"TIMESTAMP	TEXT NOT NULL,"
			"NOTE		TEXT NOT NULL,"
			"TIMEMS		REAL NOT NULL,"
			"IDTEST		INT NOT NULL);";
		CrateTable(sql);
	}

	void SqliteDriver::InserReportDataTestcase(const std::string& nameTest, const std::string& className, 
		const std::string& result, const std::string& timestamp, 
		const std::string& note, float timeMs, int idTest)
	{
		using namespace std;
		char* messageError;

		int exit = sqlite3_open(cNameSqlBase, &DB);

		string sql = "INSERT INTO REPORTS (NAMETEST, CLASSNAME, RESULT, TIMESTAMP, NOTE, TIMEMS, IDTEST) VALUES ('"+ nameTest +"','"+ className + "', '" + result + "', '" + timestamp + "', '" + note + "', " + std::to_string(timeMs) + ", " + std::to_string(idTest) + ");";

		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK)
		{
			cerr << "Error Insert\n";
			sqlite3_free(messageError);
		}
		else
		{
			cout << "Records created Successfully";
		}
	}

	void SqliteDriver::InsertData(std::string testCaseName, std::string typeTest, int countReq)
	{
		using namespace std;
		char* messageError;

		int exit = sqlite3_open(cNameSqlBase, &DB);

		string sql = "INSERT INTO COLLECTIONS (TESTCASE, STATUS, TYPETEST, TIMEMS, COUNTREQ) VALUES ('"+ testCaseName +"','','"+typeTest+"',0,"+std::to_string(countReq)+");";

		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) 
		{
			cerr << "Error Insert\n";
			sqlite3_free(messageError);
		}
		else
		{
			cout << "Records created Successfully";
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

	void SqliteDriver::CrateTable(const std::string &sql)
	{
		try
		{
			int exit = 0;
			exit = sqlite3_open(cNameSqlBase, &DB);

			char* messageError;
			exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

			if (exit != SQLITE_OK) 
			{
				std::cerr << "Error Create Table\n"<< messageError;
				sqlite3_free(messageError);
			}
			else
			{
				std::cout << "Table created Successfully\n";
			}
			sqlite3_close(DB);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what();
		}
	}
}