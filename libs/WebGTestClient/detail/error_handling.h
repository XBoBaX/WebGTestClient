#ifndef DETAIL_ERROR_HANDLING_H
#define DETAIL_ERROR_HANDLING_H

#include "errors.h"
#include <string>
#include <sstream>

namespace webdriverG {
	namespace detail {

		class Fmt {
		public:
			template<typename T>
			Fmt& operator << (const T& value) {
				stream_ << value;
				return *this;
			}

			operator std::string() const {
				return stream_.str();
			}

		private:
			std::ostringstream stream_;
		};

		template<typename T>
		bool BoolCast(T value) {
			return !!value;
		}

	}
}

#if __cplusplus >= 201103L
#define WEBDRIVER_CURRENT_FUNCTION __func__
#else
#define WEBDRIVER_CURRENT_FUNCTION __FUNCTION__
#endif

#define WEBDRIVER_FUNCTION_CONTEXT_BEGIN() \
	try {

#define WEBDRIVER_FUNCTION_CONTEXT_END() \
	} catch (const std::exception& e) { \
		throw ::webdriverG::WebDriverException(std::string(e.what()) \
			+ " called from " + WEBDRIVER_CURRENT_FUNCTION); \
	}

#define WEBDRIVER_FUNCTION_CONTEXT_END_EX(details) \
	} catch (const std::exception& e) { \
		throw ::webdriverG::WebDriverException(std::string(e.what()) \
			+ " called from " + WEBDRIVER_CURRENT_FUNCTION \
			+ " (" + std::string(details) + ")"); \
	}

#define WEBDRIVER_THROW(message) \
	throw ::webdriverG::WebDriverException(::webdriverG::detail::Fmt() \
		<< std::string(message) \
		<< " at line " << __LINE__ \
		<< ", file " << __FILE__ \
		)

#define WEBDRIVER_CHECK(pred, message) \
	for (;!detail::BoolCast(pred);) \
		WEBDRIVER_THROW(message)

#endif
