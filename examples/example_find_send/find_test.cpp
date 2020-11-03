#include "../libs/WebGTestClient.h"
#include "../libs/WebGTestClient/WebDriver.h"
#include "../../tests/environment.h"
#include "../libs/ReportingSystem.h"
#include <gtest/gtest.h>
#include <chrono>
#include <thread>

namespace test {

	using namespace webdriverG;
	using namespace reportS;

	ReportDriver systemRep("examples/example_find_send/find_test.cpp");

	class TestITC : public ::testing::Test {
	protected:
		TestITC() : browser(GetChromeDriver()) {
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(std::chrono::seconds(1));

		}

		WebDriver browser;
	};

	TEST_F(TestITC, OpenSite)
	{
		systemRep.StartRegister("OpenSite", "Feature Testing", 1);

		browser.Navigate("https://itc.ua");
		Element elem = browser.FindElement(ByClass("post"));
		elem.Click();

		std::string tittle = browser.FindElement(ByClass("entry-title")).GetText();

		ASSERT_NE(tittle, "") << "tittle is empty";

	}

	TEST_F(TestITC, OpenAuthor)
	{
		systemRep.StartRegister("OpenAuthor", "Feature Testing", 1);

		browser.FindElement(ByClass("author")).Click();
		std::string tittleH1 = browser.FindElement(ByClass("page-title")).GetText();
		ASSERT_NE(tittleH1, "") << "Can't open author page";
	}

	TEST_F(TestITC, SearchPost)
	{
		GTEST_SKIP();
		browser.FindElement(ByClass("search_btn")).Click();
		Element input = browser.FindElement(ById("s"));
		input.SendKeys("\xd0\xa1\xd0\xb8\xd1\x81\xd1\x82\xd0\xb5\xd0\xbc\xd1\x8b\x20\xd1\x81\xd0\xb8\xd0\xbd\xd1\x85\xd1\x80\xd0\xbe\xd0\xbf\xd0\xb5\xd1\x80\xd0\xb5\xd0\xb2\xd0\xbe\xd0\xb4\xd0\xb0");
		browser.FindElement(ByClass("btn-default")).Click();
		std::string tittleH2 = browser.FindElement(ByClass("entry-title")).GetText();

		ASSERT_EQ(tittleH2, "\xd0\xa1\xd0\xb8\xd1\x81\xd1\x82\xd0\xb5\xd0\xbc\xd1\x8b\x20\xd1\x81\xd0\xb8\xd0\xbd\xd1\x85\xd1\x80\xd0\xbe\xd0\xbf\xd0\xb5\xd1\x80\xd0\xb5\xd0\xb2\xd0\xbe\xd0\xb4\xd0\xb0");
	}

	TEST_F(TestITC, SearchPostWithFilter)
	{
		GTEST_SKIP();
		Element input = browser.FindElement(ById("s"));
		input.Clear();
		input.SendKeys("iphone");
		
		browser.FindElement(ByName("after")).SendKeys("06-10-2020");
		browser.FindElement(ByName("before")).SendKeys("07-10-2020");
		browser.FindElement(ByClass("btn-default")).Submit();
		std::string tittleH2 = browser.FindElement(ByClass("entry-title")).GetText();
		
		ASSERT_EQ(tittleH2, "\x41\x70\x70\x6c\x65\x20\xd0\xbd\xd0\xb0\xd0\xb7\xd0\xb2\xd0\xb0\xd0\xbb\xd0\xb0\x20\xd0\xb4\xd0\xb0\xd1\x82\xd1\x83\x20\xd0\xbf\xd1\x80\xd0\xb5\xd0\xb7\xd0\xb5\xd0\xbd\xd1\x82\xd0\xb0\xd1\x86\xd0\xb8\xd0\xb8\x20\xd0\xbd\xd0\xbe\xd0\xb2\xd1\x8b\xd1\x85\x20\x69\x50\x68\x6f\x6e\x65\x20\xe2\x80\x94\x20\x31\x33\x20\xd0\xbe\xd0\xba\xd1\x82\xd1\x8f\xd0\xb1\xd1\x80\xd1\x8f");
		getchar();
	}

	TEST_F(TestITC, CheckNavigation)
	{
		GTEST_SKIP();
		std::string nav[5]{ "news", "articles", "stati", "video", "blogs" };
		std::string navUTF8[5]{ "\xD0\x9D\xD0\xBE\xD0\xB2\xD0\xBE\xD1\x81\xD1\x82\xD0\xB8", "\xD0\x9E\xD0\xB1\xD0\xB7\xD0\xBE\xD1\x80\xD1\x8B",
			"\xD0\xA1\xD1\x82\xD0\xB0\xD1\x82\xD1\x8C\xD0\xB8", "\xD0\x92\xD0\xB8\xD0\xB4\xD0\xB5\xD0\xBE", "\xD0\x91\xD0\xBB\xD0\xBE\xD0\xB3\xD0\xB8" };
		int i = 0;
		for (auto art : nav)
		{
			browser.Navigate("https://itc.ua/" + art + "/");
			std::string tittle = browser.FindElement(ByClass("page-title")).GetText();

			ASSERT_EQ(tittle, navUTF8[i++]) << "tittle is empty";
		}
	}
}