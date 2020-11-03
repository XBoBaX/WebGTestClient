#include "reportdriver.h"

namespace reportS
{
	void ReportDriver::StartRegister(std::string testCaseName, std::string typeTest, int countReq)
	{
		SqliteDriver SQLdr;
		SQLdr.InsertData(testCaseName, typeTest, countReq);
	}
}