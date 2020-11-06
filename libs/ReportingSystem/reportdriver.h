#ifndef REPORTS_REPORTDRIVER_H
#define REPORTS_REPORTDRIVER_H

#include "sqliteDriver.h"
#include "../../tests/lib/rapidxml-1.13/rapidxml.hpp"
#include "../../tests/lib/rapidxml-1.13/rapidxml_print.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

namespace reportS
{
	class ReportDriver 
	{
	public:
		ReportDriver() {};
		ReportDriver(std::string path, int timeS) : pathToFile(path), timeSleep(timeS) {};
		void StartRegister(std::string, std::string, int);
		void ParseResult();
	private:
		std::string pathToFile;
		int timeSleep { 1 };
		int idTestNow{ 0 };
	};

}

#endif