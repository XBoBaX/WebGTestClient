#ifndef WEBDRIVERG_WEBDRIVER_H
#define WEBDRIVERG_WEBDRIVER_H

#include "client.h"
#include "session.h"

namespace webdriverG {

	// The main class for interactions with a server. Automatically connects to a server,
	// creates and deletes a session and gives access to session's API.
	class WebDriver // copyable
		: public Client
		, public Session {
	public:
		explicit WebDriver(
			const Capabilities& desired = Capabilities(),
			const Capabilities& required = Capabilities(),
			const std::string& url = kDefaultWebDriverUrl
		)
			: Client(url)
			, Session(CreateSession(desired, required))
		{}
	};

	inline
		WebDriver Start(
			const Capabilities& desired,
			const Capabilities& required = Capabilities(),
			const std::string& url = kDefaultWebDriverUrl
		)
	{
		return WebDriver(desired, required, url);
	}

	inline
		WebDriver Start(const Capabilities& desired, const std::string& url)
	{
		return Start(desired, Capabilities(), url);
	}

}

#endif