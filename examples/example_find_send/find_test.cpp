#include "../libs/WebGTestClient.h"
#include "../libs/WebGTestClient/WebDriver.h"
#include <gtest/gtest.h>
#include "../../tests/environment.h"

namespace test {

	using namespace webdriverG;
	
	class TestITC : public ::testing::Test {
	protected:
		TestITC() : browser(GetChromeDriver()) {}

		WebDriver browser;
	};

	TEST_F(TestITC, OpenSite)
	{
		browser.Navigate("https://itc.ua");
		Element elem = browser.FindElement(ByClass("post"));
		elem.Click();

		std::string tittle = browser.FindElement(ByClass("entry-title")).GetText();

		ASSERT_NE(tittle, "") << "tittle is empty";
	}

	TEST_F(TestITC, OpenAuthor)
	{
		browser.FindElement(ByClass("author")).Click();
		std::string tittleH1 = browser.FindElement(ByClass("page-title")).GetText();
		
		ASSERT_NE(tittleH1, "") << "Can't open author page";
	}

	TEST_F(TestITC, SearchBlog)
	{
		browser.FindElement(ByClass("search_btn")).Click();
		Element input = browser.FindElement(ById("s"));
		input.SendKeys("\xd0\xa1\xd0\xb8\xd1\x81\xd1\x82\xd0\xb5\xd0\xbc\xd1\x8b\x20\xd1\x81\xd0\xb8\xd0\xbd\xd1\x85\xd1\x80\xd0\xbe\xd0\xbf\xd0\xb5\xd1\x80\xd0\xb5\xd0\xb2\xd0\xbe\xd0\xb4\xd0\xb0");
		browser.FindElement(ByClass("btn-default")).Click();
		std::string tittleH2 = browser.FindElement(ByClass("entry-title")).GetText();

		ASSERT_EQ(tittleH2, "\xd0\xa1\xd0\xb8\xd1\x81\xd1\x82\xd0\xb5\xd0\xbc\xd1\x8b\x20\xd1\x81\xd0\xb8\xd0\xbd\xd1\x85\xd1\x80\xd0\xbe\xd0\xbf\xd0\xb5\xd1\x80\xd0\xb5\xd0\xb2\xd0\xbe\xd0\xb4\xd0\xb0");
	}
}