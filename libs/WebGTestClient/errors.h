#ifndef ERRORS_H
#define ERRORS_H

#include <stdexcept>
#include <string>

namespace webdriverG {

	struct WebDriverException : std::runtime_error {
		explicit WebDriverException(const std::string& message)
			: std::runtime_error(message) {}
	};

} 

#endif
