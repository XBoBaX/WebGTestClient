#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


#include "../libs/WebGTestClient/WebDriver.h"
#include "../libs/WebGTestClient/capabilities.h"
#include <string>

namespace test {

	const char* const kDefaultTestWebDriverUrl = "http://localhost:7777/";
	const char* const kDefaultTestPagesUrl = "http://localhost:8080/";

	struct Parameters {
		std::string web_driver_url;
		webdriver::Capabilities required;
		webdriver::Capabilities desired;
		std::string test_pages_url;
		bool test_real_browsers;

		Parameters()
			: web_driver_url(kDefaultTestWebDriverUrl)
			, test_pages_url(kDefaultTestPagesUrl)
			, test_real_browsers(false)
		{}
	};

};

#endif