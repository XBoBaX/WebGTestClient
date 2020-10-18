#ifndef DETAIL_HTTP_CONNECTION_H
#define DETAIL_HTTP_CONNECTION_H

#include "http_client.h"
#include "http_request.h"
#include "error_handling.h"
#include "shared.h"
#include <curl/curl.h>

namespace webdriver {
	namespace detail {

		class HttpConnection // noncopyable
			: public IHttpClient
			, public SharedObjectBase
		{
		public:
			HttpConnection()
				: connection_(InitCurl())
			{}

			~HttpConnection() {
				curl_easy_cleanup(connection_);
			}

			HttpResponse Get(const std::string& url) const {
				return HttpGetRequest(connection_, url).Execute();
			}

			HttpResponse Delete(const std::string& url) const {
				return HttpDeleteRequest(connection_, url).Execute();
			}

			HttpResponse Post(
				const std::string& url,
				const std::string& upload_data
			) const {
				return HttpPostRequest(connection_, url, upload_data).Execute();
			}

		private:
			static
				CURL* InitCurl() {
				CURL* const result = curl_easy_init();
				WEBDRIVER_CHECK(result, "Cannot initialize CURL");
				return result;
			}

		private:
			CURL* const connection_;
		};

	} 
}
#endif