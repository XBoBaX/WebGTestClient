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
	using namespace rapidxml;

	class ReportDriver 
	{
	public:
		ReportDriver() {};
		ReportDriver(std::string path, int timeS) : pathToFile(path), timeSleep(timeS) {};
		void StartRegister(std::string, std::string, int);
		void ParseResult();
	private:
		void SetTestsuites(const xml_node<> *);
		void SetTestcase(int, const xml_node<> *) const;
		void SetTescaeLoop(const xml_node<> *) const;

		std::string pathToFile;
		std::string totalTimeStamp{""};
		int timeSleep { 1 };
		int countTest { 0 };
		int idTestNow { 0 };
		const char *nameNode[3]{"testsuites", "testsuite", "testcase"};
	};

}

#endif