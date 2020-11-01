#include "environment.h"
#include "../libs/WebGTestClient/WebDriver.h"
#include <gtest/gtest.h>

namespace test {

	using namespace webdriver;

	TEST(test_case_name, test_name) 
	{
		ASSERT_EQ(1, 1) << "1 is not equal 0";
	}

}