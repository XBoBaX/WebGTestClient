#ifndef BROWSERS_CHROME_H
#define BROWSERS_CHROME_H

#include "../capabilities.h"

namespace webdriverG {
	namespace chrome {

		struct PerfLoggingPrefs : JsonObject {
			WEBDRIVER_PROPERTIES_BEGIN(PerfLoggingPrefs)
				WEBDRIVER_PROPERTY(EnableNetwork, "enableNetwork", bool)
				WEBDRIVER_PROPERTY(enablePage, "enablePage", bool)
				WEBDRIVER_PROPERTY(enableTimeline, "enableTimeline", bool)
				WEBDRIVER_PROPERTY(tracingCategories, "tracingCategories", std::string)
				WEBDRIVER_PROPERTY(bufferUsageReportingInterval, "bufferUsageReportingInterval", int)
				WEBDRIVER_PROPERTIES_END()
		};

	} // namespace chrome

	struct Chrome : Capabilities { // copyable
		Chrome(const Capabilities& defaults = Capabilities())
			: Capabilities(defaults) {
			SetBrowserName(browser::Chrome);
			SetVersion("");
			SetPlatform(platform::Any);
		}

		// See https://sites.google.com/a/chromium.org/chromedriver/capabilities for details
		WEBDRIVER_PROPERTIES_BEGIN(Chrome)
			WEBDRIVER_PROPERTY(LoggingPrefs, "loggingPrefs", LoggingPrefs)
			WEBDRIVER_PROPERTY(Args, "args", std::vector<std::string>)
			WEBDRIVER_PROPERTY(Binary, "binary", std::string)
			// Each extension is a base64-encoded .crx file
			WEBDRIVER_PROPERTY(Extensions, "extensions", std::vector<std::string>)
			WEBDRIVER_PROPERTY(LocalState, "localState", JsonObject)
			WEBDRIVER_PROPERTY(Prefs, "prefs", JsonObject)
			WEBDRIVER_PROPERTY(Detach, "detach", bool)
			WEBDRIVER_PROPERTY(DebuggerAddress, "debuggerAddress", std::string)
			WEBDRIVER_PROPERTY(ExcludeSwitches, "excludeSwitches", std::vector<std::string>)
			WEBDRIVER_PROPERTY(MinidumpPath, "minidumpPath", std::string)
			WEBDRIVER_PROPERTY(MobileEmulation, "mobileEmulation", JsonObject)
			WEBDRIVER_PROPERTY(PerfLoggingPrefs, "perfLoggingPrefs", chrome::PerfLoggingPrefs)
			WEBDRIVER_PROPERTIES_END()
	};

}

#endif