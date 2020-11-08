#ifndef SQLITEDRIVER_H
#define SQLITEDRIVER_H

#include <string>
#include <sqlite3.h>
#include <iostream>
#include <vector>

namespace reportS {	

	class SqliteDriver
	{
	public:
		SqliteDriver();
		~SqliteDriver() {};

		void InsertData(std::string, std::string, int);
		void InserReportDataTestcase(const std::string&, const std::string&, const std::string&, 
			const std::string&, const std::string&, float, int);
		std::string GetData(std::string, std::string);
		void GetListTimeStamp();
		void GetFromCollections(std::string);
		std::vector<std::string> arrayTime;
	private:
		void CreateDB();
		void CrateTable(const std::string& sql);
		void ClearArr();

		const char *cNameSqlBase = "reportTests.db";
		sqlite3* DB;
	};

}

#endif