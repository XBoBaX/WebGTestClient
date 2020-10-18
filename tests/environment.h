#ifndef ENVIRONMENT_H
#define WEBDRIVERXX_ENVIRONMENT_H

#include "../libs/WebGTestClient/WebDriver.h"
#include "../libs/WebGTestClient/capabilities.h"
#include <gtest/gtest.h>
#include <string>
#include <algorithm>

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

	class Environment : public ::testing::Environment {
	public:
		static Environment& Instance() {
			return *instance_;
		}

		explicit Environment(const Parameters& parameters)
			: driver_(0)
			, parameters_(parameters)
		{}

		webdriver::WebDriver& GetDriver() {
			return driver_ ? *driver_ : GetFreshDriver();
		}

		webdriver::WebDriver& GetFreshDriver() {
			DeleteDriver();
			driver_ = new webdriver::WebDriver(CreateDriver());
			return *driver_;
		}

		webdriver::WebDriver CreateDriver() {
			return webdriver::WebDriver(
				parameters_.desired,
				parameters_.required,
				parameters_.web_driver_url
			);
		}

		std::string GetWebDriverUrl() const { return parameters_.web_driver_url; }

		Parameters GetParameters() const { return parameters_; }

		std::string GetTestPageUrl(const std::string& page_name) const {
			std::string url = parameters_.test_pages_url;
			if (!url.empty() && url[url.length() - 1] != '/')
				url += "/";
			url += page_name;
			return url;
		}

	private:
		void SetUp() {
			instance_ = this;
		}

		void TearDown() {
			instance_ = 0;
			DeleteDriver();
		}

		void DeleteDriver() {
			delete driver_;
			driver_ = 0;
		}

	private:
		static Environment* instance_;
		webdriver::WebDriver* driver_;
		Parameters parameters_;
	};

	inline Parameters GetParameters() { return Environment::Instance().GetParameters(); }
	inline std::string GetWebDriverUrl() { return Environment::Instance().GetWebDriverUrl(); }
	inline std::string GetTestPageUrl(const std::string& page_name) { return Environment::Instance().GetTestPageUrl(page_name); }
	inline webdriver::WebDriver& GetDriver() { return Environment::Instance().GetDriver(); }
	inline webdriver::WebDriver& GetFreshDriver() { return Environment::Instance().GetFreshDriver(); }
	inline webdriver::WebDriver CreateDriver() { return Environment::Instance().CreateDriver(); }
	inline bool TestRealBrowsers() { return GetParameters().test_real_browsers; }
	inline std::string GetBrowserName() { return GetDriver().GetCapabilities().GetBrowserName(); }
	inline bool IsFirefox() { return GetBrowserName() == webdriver::browser::Firefox; }
	inline bool IsPhantom() { return GetBrowserName() == webdriver::browser::Phantom; }

} 

#endif
