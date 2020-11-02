#include "environment.h"
#include "../libs/WebGTestClient/session.h"
#include <gtest/gtest.h>
#include <algorithm>

namespace test {

	using namespace webdriverG;

	class TestSession : public ::testing::Test {
	protected:
		TestSession() : driver(GetChromeDriver()) {}

		void ReplaceSpoiledSession() {
			driver = GetFreshChromeDriver();
		}

		WebDriver driver;
	};

	TEST_F(TestSession, StartsSecondBrowser) {
		WebDriver second = CreateAndStart();
	}

	TEST_F(TestSession, GetsCurrentWindow) {
		driver.GetCurrentWindow();
	}

	TEST_F(TestSession, GetsWindowHandle) {
		ASSERT_NE("", driver.GetCurrentWindow().GetHandle());
	}

	TEST_F(TestSession, ClosesCurrentWindow) {
		driver.CloseCurrentWindow();
		ReplaceSpoiledSession();
	}

	TEST_F(TestSession, GetsWindowSize) {
		Window window = driver.GetCurrentWindow();
		window.GetSize();
	}

	TEST_F(TestSession, SetsWindowPosition) {
		if (IsPhantom()) return;
		Window window = driver.GetCurrentWindow();
		Point position1;
		position1.x = 101;
		position1.y = 102;
		window.SetPosition(position1);
		Point position2 = window.GetPosition();
		ASSERT_EQ(101, position2.x);
		ASSERT_EQ(102, position2.y);
	}

	TEST_F(TestSession, MaximizesWindow) {
		Window window = driver.GetCurrentWindow();
		window.Maximize();
	}

	TEST_F(TestSession, GetsWindows) {
		driver.GetWindows();
	}

	TEST_F(TestSession, Navigates) {
		std::string url = GetWebDriverUrl() + "status";
		driver.Navigate(url);
		ASSERT_EQ(url, driver.GetUrl());
	}

	TEST_F(TestSession, SetsTimeouts) {
		driver.SetTimeoutMs(timeout::Implicit, 1000);
		driver.SetTimeoutMs(timeout::PageLoad, 1000);
		driver.SetTimeoutMs(timeout::Script, 1000);
	}

	Cookie FindCookie(
		const std::vector<Cookie>& cookies,
		const std::string& name,
		const Cookie& default_value = Cookie()
	) {
		const auto it = std::find_if(cookies.begin(), cookies.end(),
			[&name](const Cookie& cookie) {
				return cookie.name == name;
			});
		return it != cookies.end() ? *it : default_value;
	}

	namespace webdriverG {

		void PrintTo(const Cookie& c, ::std::ostream* os) {
			*os << ToJson(c).serialize();
		}

	} 
} // namespace test
