#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "../libs/WebGTestClient/WebDriver.h"
#include "../libs/WebGTestClient/capabilities.h"
#include "../libs/WebGTestClient/browsers/chrome.h"
#include <gtest/gtest.h>
#include <string>
#include <algorithm>

namespace test {

	const char* const kDefaultTestWebDriverUrl = "http://localhost:7777/wd/hub";
	//You need start apache server on your machine
	const char* const kDefaultTestPagesUrl = "http://localhost:8080/"; 

	struct Parameters {
		std::string web_driver_url;
		webdriverG::Capabilities required;
		webdriverG::Capabilities desired;
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

		webdriverG::WebDriver& GetDriver() {
			return driver_ ? *driver_ : GetFreshDriver();
		}
		
		webdriverG::WebDriver& GetChromeDriver() {
			return driver_ ? *driver_ : GetFreshChromeDriver();
		}

		webdriverG::WebDriver& GetFreshChromeDriver() {
			DeleteDriver();
			driver_ = new webdriverG::WebDriver(CreateAndStart());
			return *driver_;
		}

		webdriverG::WebDriver& GetFreshDriver() {
			DeleteDriver();
			driver_ = new webdriverG::WebDriver();
			return *driver_;
		}

		webdriverG::WebDriver CreateDriver() {
			return webdriverG::WebDriver(
				parameters_.desired,
				parameters_.required,
				parameters_.web_driver_url
			);
		}
		
		webdriverG::WebDriver CreateAndStart() {
			using namespace webdriverG;
			parameters_.desired = Chrome();
			return webdriverG::WebDriver(
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
		webdriverG::WebDriver* driver_;
		Parameters parameters_;
	};

	inline Parameters GetParameters() { return Environment::Instance().GetParameters(); }
	inline std::string GetWebDriverUrl() { return Environment::Instance().GetWebDriverUrl(); }
	inline std::string GetTestPageUrl(const std::string& page_name) { return Environment::Instance().GetTestPageUrl(page_name); }
	inline webdriverG::WebDriver& GetDriver() { return Environment::Instance().GetDriver(); }
	inline webdriverG::WebDriver& GetChromeDriver() { return Environment::Instance().GetChromeDriver(); }
	inline webdriverG::WebDriver& GetFreshDriver() { return Environment::Instance().GetFreshDriver(); }
	inline webdriverG::WebDriver& GetFreshChromeDriver() { return Environment::Instance().GetFreshChromeDriver(); }
	inline webdriverG::WebDriver CreateDriver() { return Environment::Instance().CreateDriver(); }
	inline webdriverG::WebDriver CreateAndStart() { return Environment::Instance().CreateAndStart(); }
	inline bool TestRealBrowsers() { return GetParameters().test_real_browsers; }
	inline std::string GetBrowserName() { return GetDriver().GetCapabilities().GetBrowserName(); }
	inline bool IsFirefox() { return GetBrowserName() == webdriverG::browser::Firefox; }
	inline bool IsPhantom() { return GetBrowserName() == webdriverG::browser::Phantom; }

} 

#endif
