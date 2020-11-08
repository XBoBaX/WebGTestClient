#include "../libs/WebGTestClient.h"
#include "../../tests/environment.h"
#include <gtest/gtest.h>

using namespace webdriverG;

namespace test {

	Environment* Environment::instance_ = 0;

	bool IsCommandLineArgument(const std::string& arg, const char* name) {
		return arg.find(std::string("--") + name) == 0;
	}

	std::string GetCommandLineArgumentValue(const std::string& arg) {
		const size_t pos = arg.find('=');
		return pos == std::string::npos ? std::string() : arg.substr(pos + 1);
	}

	Parameters ParseParameters(int argc, char** argv) {
		Parameters result;
		for (int i = 1; i < argc; ++i) {
			const std::string arg = argv[i];
			if (IsCommandLineArgument(arg, "browser")) {
				result.web_driver_url = webdriverG::kDefaultWebDriverUrl;
				const std::string browser_name = GetCommandLineArgumentValue(arg);
				result.desired.Set("browserName", browser_name);
			}
			else if (IsCommandLineArgument(arg, "pages")) {
				result.test_pages_url = GetCommandLineArgumentValue(arg);
			}
			else if (IsCommandLineArgument(arg, "webdriver")) {
				result.web_driver_url = GetCommandLineArgumentValue(arg);
			}
			else if (IsCommandLineArgument(arg, "test_real_browsers")) {
				result.test_real_browsers = true;
			}
		}
		return result;
	}
}

#include "../libs/ReportingSystem.h"

int main(int argc, char** argv)
{
	::testing::GTEST_FLAG(output) = "xml:report.xml";
	::testing::InitGoogleTest(&argc, argv);
	::testing::AddGlobalTestEnvironment(
		new test::Environment(test::ParseParameters(argc, argv))
	);

	using namespace reportS;

	//int flagReturnTests = RUN_ALL_TESTS();
	

	ReportDriver systemRep = ReportDriver();
	//systemRep.ParseResult();
	systemRep.CreateReport();
	
	/*if (flagReturnTests != 0)
	{
		return flagReturnTests;
	}*/
	return 0;
}