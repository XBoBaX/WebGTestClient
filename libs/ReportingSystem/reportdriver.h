#ifndef REPORTS_REPORTDRIVER_H
#define REPORTS_REPORTDRIVER_H

#include "sqliteDriver.h"
#include <iostream>
#include <string>

namespace reportS
{
	class ReportDriver 
	{
	public:
		ReportDriver() {};
		ReportDriver(std::string path) : pathToFile(path) {};
		void StartRegister(std::string, std::string, int);
	private:
		std::string pathToFile;
		int idTestNow{ 0 };
	};

}

#endif