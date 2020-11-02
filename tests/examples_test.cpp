#include "environment.h"
#include "../libs/WebGTestClient.h"
#ifndef WEBDRIVER_ENABLE_GMOCK_MATCHERS
#define WEBDRIVER_ENABLE_GMOCK_MATCHERS
#endif
#include "../libs/WebGTestClient/wait_match.h"
#include <gtest/gtest.h>

namespace test {

	using namespace webdriverG;

	class TestExamples : public ::testing::Test {
	protected:
		TestExamples() : driver(GetChromeDriver()) {}

		WebDriver driver;
	};

	TEST_F(TestExamples, QuickExample) {
		driver
			.Navigate("http://google.com")
			.FindElement(ByCss("input[name=q]"))
			.SendKeys("Hello, world!")
			.Submit();
	}

	TEST_F(TestExamples, ExplicitWait1) {
		auto find_element = [&] { return driver.FindElement(ById("async_loaded")); };
		try {
			int timeout = 0;
			Element element = WaitForValue(find_element, timeout);
			FAIL();
		}
		catch (const std::exception&) {}
	}

	TEST_F(TestExamples, ExplicitWait2) {
		auto element_is_selected = [&] {
			return driver.FindElement(ById("async_loaded")).IsSelected();
		};
		try {
			int timeout = 0;
			WaitUntil(element_is_selected, timeout);
			FAIL();
		}
		catch (const std::exception&) {}
	}

} // namespace test
