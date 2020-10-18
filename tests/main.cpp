#include "environment.h"
#include <gtest/gtest.h>
#include <string>

//namespace test {
//
//	Environment* Environment::instance_ = 0;
//
//	Parameters ParseParameters(int argc, char** argv) {
//		Parameters result;
//		for (int i = 1; i < argc; ++i) {
//			const std::string arg = argv[i];
//			if (IsCommandLineArgument(arg, "browser")) {
//				result.web_driver_url = webdriver::kDefaultWebDriverUrl;
//				const std::string browser_name = GetCommandLineArgumentValue(arg);
//				result.desired.Set("browserName", browser_name);
//			}
//			else if (IsCommandLineArgument(arg, "pages")) {
//				result.test_pages_url = GetCommandLineArgumentValue(arg);
//			}
//			else if (IsCommandLineArgument(arg, "webdriver")) {
//				result.web_driver_url = GetCommandLineArgumentValue(arg);
//			}
//			else if (IsCommandLineArgument(arg, "test_real_browsers")) {
//				result.test_real_browsers = true;
//			}
//		}
//		return result;
//	}
//}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	/*::testing::AddGlobalTestEnvironment(
		new test::Environment(test::ParseParameters(argc, argv))
	);*/
	
	std::cout << "Hello World!\n";

	return RUN_ALL_TESTS();
}
