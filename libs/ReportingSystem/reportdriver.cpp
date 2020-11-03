#include "reportdriver.h"

namespace reportS
{
	void ReportDriver::StartRegister(std::string testCaseName, std::string typeTest, int countReq)
	{
		std::cout << "\n\n" << testCaseName << "\n" << typeTest << "\n" << countReq << "\n";
	}
}