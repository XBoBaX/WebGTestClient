#include "environment.h"
#include "../libs/WebGTestClient/detail/http_connection.h"
#include <gtest/gtest.h>
#include <string>

namespace test {

	using namespace webdriver;
	using namespace webdriver::detail;

	TEST(HttpConnection, CanBeCreated) {
		HttpConnection connection;
	}

	TEST(HttpConnection, ThrowsExceptionIfPortIsClosed) {
		HttpConnection connection;
		const char* const kUrlWithClosedPort = "http://127.0.0.1:7778/";
		ASSERT_THROW(connection.Get(kUrlWithClosedPort), WebDriverException);
	}

} // namespace test
