#include "environment.h"
#include "../libs/WebGTestClient/WebDriver.h"
#include <gtest/gtest.h>

namespace test {

	using namespace webdriver;

	TEST(test_case_name, test_name) 
	{
		ASSERT_EQ(1, 1) << "1 is not equal 0";
	}

	/*TEST(WebDriver, CreatesSession) {
		Client client(GetWebDriverUrl());
		size_t number_of_sessions_before = client.GetSessions().size();
		WebDriver testee = CreateDriver();
		size_t number_of_sessions_after = client.GetSessions().size();
		ASSERT_EQ(number_of_sessions_before + 1, number_of_sessions_after);
	}*/

}