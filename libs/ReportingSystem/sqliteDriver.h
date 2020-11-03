#ifndef SQLITEDRIVER_H
#define SQLITEDRIVER_H

#include <string>
#include <sqlite3.h>
#include <iostream>

namespace reportS {	

	class SqliteDriver
	{
	public:
		SqliteDriver();
		~SqliteDriver() {};

		void InsertData(std::string, std::string, int);
	private:
		void CreateDB();
		void CrateTable();
		const char *cNameSqlBase = "reportTests.db";
		sqlite3* DB;
	};

}

#endif