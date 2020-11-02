#ifndef WEBDRIVER_CAPABILITIES_H
#define WEBDRIVER_CAPABILITIES_H

#include "conversions.h"
#include "picojson.h"
#include <string>

namespace webdriverG {

	namespace browser {
		typedef std::string Value;
		typedef const char* const ConstValue;
		ConstValue Android = "android";
		ConstValue Chrome = "chrome";
		ConstValue Firefox = "firefox";
		ConstValue HtmlUnit = "htmlunit";
		ConstValue InternetExplorer = "internet explorer";
		ConstValue IPhone = "iPhone";
		ConstValue IPad = "iPad";
		ConstValue Mock = "mock";
		ConstValue Opera = "opera";
		ConstValue Safari = "safari";
		ConstValue Phantom = "phantomjs";
	} // namespace browser

	namespace platform {
		typedef std::string Value;
		typedef const char* const ConstValue;
		ConstValue Any = "ANY";
		ConstValue Windows = "WINDOWS";
		ConstValue Xp = "XP";
		ConstValue Vista = "VISTA";
		ConstValue Mac = "MAC";
		ConstValue Linux = "LINUX";
		ConstValue Unix = "UNIX";
		ConstValue Android = "ANDROID";
	} // namespace platform

	namespace unexpected_alert_behaviour {
		typedef std::string Value;
		typedef const char* const ConstValue;
		ConstValue Accept = "accept";
		ConstValue Dismiss = "dismiss";
		ConstValue Ignore = "ignore";
	} // namespace unexpected_alert_behaviour

	namespace proxy_type {
		typedef std::string Value;
		typedef const char* const ConstValue;
		ConstValue Direct = "direct";
		ConstValue Manual = "manual"; // Manual proxy settings configured, e.g. setting a proxy for HTTP, a proxy for FTP
		ConstValue Pac = "pac"; // Proxy autoconfiguration from a URL
		ConstValue Autodetect = "autodetect"; // Proxy autodetection, probably with WPAD
		ConstValue System = "system"; // Use system settings
	} // namespace proxy_type

#define WEBDRIVER_PROPERTIES_BEGIN(this_class)	typedef this_class This;
#define WEBDRIVER_PROPERTIES_END()

#define WEBDRIVER_PROPERTY_RONLY(name, id, type) \
	type Get##name() const { return GetOptional<type>(id); } \
	bool Has##name() { return Has(id); }

#define WEBDRIVER_PROPERTY(name, id, type) \
	WEBDRIVER_PROPERTY_RONLY(name, id, type) \
	This& Set##name(const type& value) { Set(id, value); return *this; }

	struct Proxy : JsonObject { // copyable
		WEBDRIVER_PROPERTIES_BEGIN(Proxy)
			WEBDRIVER_PROPERTY(ProxyType, "proxyType", proxy_type::Value)
			WEBDRIVER_PROPERTIES_END()
	};

	struct DirectConnection : Proxy { // copyable
		DirectConnection() { SetProxyType(proxy_type::Direct); }
	};

	struct AutodetectProxy : Proxy { // copyable
		AutodetectProxy() { SetProxyType(proxy_type::Autodetect); }
	};

	struct SystemProxy : Proxy { // copyable
		SystemProxy() { SetProxyType(proxy_type::System); }
	};

	struct AutomaticProxyFromUrl : Proxy { // copyable
		explicit AutomaticProxyFromUrl(const std::string& url) {
			SetProxyType(proxy_type::Pac);
			SetAutoconfigUrl(url);
		}

		WEBDRIVER_PROPERTIES_BEGIN(AutomaticProxyFromUrl)
			WEBDRIVER_PROPERTY(AutoconfigUrl, "proxyAutoconfigUrl", std::string)
			WEBDRIVER_PROPERTIES_END()
	};

	struct ManualProxy : Proxy { // copyable
		ManualProxy() { SetProxyType(proxy_type::Manual); }

		WEBDRIVER_PROPERTIES_BEGIN(ManualProxy)
			WEBDRIVER_PROPERTY(NoProxyFor, "noProxy", std::string)
			WEBDRIVER_PROPERTIES_END()
	};

	struct FtpProxy : ManualProxy { // copyable
		explicit FtpProxy(const std::string& address) { SetProxyAddress(address); }

		WEBDRIVER_PROPERTIES_BEGIN(FtpProxy)
			WEBDRIVER_PROPERTY(ProxyAddress, "ftpProxy", std::string)
			WEBDRIVER_PROPERTIES_END()
	};

	struct HttpProxy : ManualProxy { // copyable
		explicit HttpProxy(const std::string& address) { SetProxyAddress(address); }

		WEBDRIVER_PROPERTIES_BEGIN(HttpProxy)
			WEBDRIVER_PROPERTY(ProxyAddress, "httpProxy", std::string)
			WEBDRIVER_PROPERTIES_END()
	};

	struct SslProxy : ManualProxy { // copyable
		explicit SslProxy(const std::string& address) { SetProxyAddress(address); }

		WEBDRIVER_PROPERTIES_BEGIN(SslProxy)
			WEBDRIVER_PROPERTY(ProxyAddress, "sslProxy", std::string)
			WEBDRIVER_PROPERTIES_END()
	};

	struct SocksProxy : ManualProxy { // copyable
		explicit SocksProxy(const std::string& address) { SetProxyAddress(address); }

		WEBDRIVER_PROPERTIES_BEGIN(SocksProxy)
			WEBDRIVER_PROPERTY(ProxyAddress, "socksProxy", std::string)
			WEBDRIVER_PROPERTY(Username, "socksUsername", std::string)
			WEBDRIVER_PROPERTY(Password, "socksPassword", std::string)
			WEBDRIVER_PROPERTIES_END()
	};

	namespace log_level {
		typedef std::string Value;
		typedef const char* const ConstValue;
		ConstValue Off = "OFF";
		ConstValue Severe = "SEVERE";
		ConstValue Warning = "WARNING";
		ConstValue Info = "INFO";
		ConstValue Config = "CONFIG";
		ConstValue Fine = "FINE";
		ConstValue Finer = "FINER";
		ConstValue Finest = "FINEST";
		ConstValue All = "ALL";
	} // namespace log_level

	struct LoggingPrefs : JsonObject {
		WEBDRIVER_PROPERTIES_BEGIN(LoggingPrefs)
			WEBDRIVER_PROPERTY(Level, "driver", log_level::Value)
			WEBDRIVER_PROPERTIES_END()
	};

	// List of keys and values indicating features that server can or should provide.
	struct Capabilities : JsonObject { // copyable
		Capabilities() {}
		explicit Capabilities(const picojson::object& object) : JsonObject(object) {}

		// Hardcoded capabilities are here just to add some sugar.
		// If a capability is not listed below use Get/Set/Has public members.

		WEBDRIVER_PROPERTIES_BEGIN(Capabilities)
			WEBDRIVER_PROPERTY(BrowserName, "browserName", browser::Value)
			WEBDRIVER_PROPERTY(Version, "version", std::string)
			WEBDRIVER_PROPERTY(Platform, "platform", platform::Value)

			WEBDRIVER_PROPERTY_RONLY(TakesScreenshot, "takesScreenshot", bool)
			WEBDRIVER_PROPERTY_RONLY(HandlesAlerts, "handlesAlerts", bool)
			WEBDRIVER_PROPERTY_RONLY(CssSelectorsEnabled, "cssSelectorsEnabled", bool)

			WEBDRIVER_PROPERTY(JavascriptEnabled, "javascriptEnabled", bool)
			WEBDRIVER_PROPERTY(DatabaseEnabled, "databaseEnabled", bool)
			WEBDRIVER_PROPERTY(LocationContextEnabled, "locationContextEnabled", bool)
			WEBDRIVER_PROPERTY(ApplicationCacheEnabled, "applicationCacheEnabled", bool)
			WEBDRIVER_PROPERTY(BrowserConnectionEnabled, "browserConnectionEnabled", bool)
			WEBDRIVER_PROPERTY(WebStorageEnabled, "webStorageEnabled", bool)
			WEBDRIVER_PROPERTY(AcceptSslCerts, "acceptSslCerts", bool)
			WEBDRIVER_PROPERTY(Rotatable, "rotatable", bool)
			WEBDRIVER_PROPERTY(NativeEvents, "nativeEvents", bool)
			WEBDRIVER_PROPERTY(Proxy, "proxy", Proxy)
			WEBDRIVER_PROPERTY(UnexpectedAlertBehaviour, "unexpectedAlertBehaviour", unexpected_alert_behaviour::Value)
			WEBDRIVER_PROPERTY(ElementScrollBehavior, "elementScrollBehavior", int)

			WEBDRIVER_PROPERTY_RONLY(SessionId, "webdriver.remote.sessionid", std::string)
			WEBDRIVER_PROPERTY(QuietExceptions, "webdriver.remote.quietExceptions", bool)
			WEBDRIVER_PROPERTIES_END()
	};

	inline
		void CustomFromJson(const picojson::value& value, Capabilities& result) {
		WEBDRIVER_CHECK(value.is<picojson::object>(), "Capabilities is not an object");
		result = Capabilities(value.get<picojson::object>());
	}

}

#endif
