#include "environment.h"
#include <gtest/gtest.h>
#include <string>

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
				result.web_driver_url = webdriver::kDefaultWebDriverUrl;
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

#include "../libs/WebGTestClient.h"
#include "../libs/WebGTestClient/browsers/chrome.h"

using namespace webdriver;

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	::testing::AddGlobalTestEnvironment(
		new test::Environment(test::ParseParameters(argc, argv))
	);
	
	//std::cout << "Hello World!\n";
	//WebDriver chrome = Start(Chrome());
	//chrome.Navigate("http://google.com").FindElement(ByCss("input[name=q]")).SendKeys("Hello, world!").Submit();
	//int a;
	//std::cin >> a;
	return RUN_ALL_TESTS();
}
