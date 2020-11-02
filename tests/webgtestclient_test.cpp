#include "environment.h"
#include "../libs/WebGTestClient.h"
#include <gtest/gtest.h>

namespace test {

using namespace webdriverG;

TEST(WebDriver, CreatesSession) {
	Client client(GetWebDriverUrl());
	size_t number_of_sessions_before = client.GetSessions().size();
	//WebDriver testee = CreateDriver(); 
	WebDriver testee = CreateAndStart();
	size_t number_of_sessions_after = client.GetSessions().size();
	ASSERT_EQ(number_of_sessions_before + 1, number_of_sessions_after);
}

TEST(WebDriver, DeletesSessionOnDestruction) {
	Client client(GetWebDriverUrl());
	size_t number_of_sessions_before = 0;
	{
		WebDriver testee = CreateAndStart();
		number_of_sessions_before = client.GetSessions().size();
	}
	size_t number_of_sessions_after = client.GetSessions().size();
	ASSERT_EQ(number_of_sessions_before - 1, number_of_sessions_after);
}

TEST(WebDriver, IsCopyable) {
	WebDriver driver1(GetChromeDriver());
	const WebDriver driver2 = driver1;
	WebDriver driver3 = driver1;
	driver3 = driver2;
	ASSERT_NO_THROW(GetChromeDriver().GetSessions());
	ASSERT_NO_THROW(driver1.GetSessions());
	ASSERT_NO_THROW(driver2.GetSessions());
	ASSERT_NO_THROW(driver3.GetSessions());
}

TEST(WebDriver, CopyableToClient) {
	WebDriver driver = GetDriver();
	Client client = driver;
	ASSERT_NO_THROW(client.GetSessions());
	ASSERT_NO_THROW(driver.GetSessions());
}

TEST(WebDriver, CopyableToSession) {
	WebDriver driver = GetDriver();
	Session session = driver;
	ASSERT_NO_THROW(session.GetWindows());
	ASSERT_NO_THROW(driver.GetWindows());
}

} // namespace test
