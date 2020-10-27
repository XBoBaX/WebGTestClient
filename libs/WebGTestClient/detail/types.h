#ifndef DETAIL_TYPES_H
#define DETAIL_TYPES_H

#include "../conversions.h"
#include "../capabilities.h"
#include "../picojson.h"
#include <string>

namespace webdriver {
	namespace detail {

		struct SessionRef {
			std::string id;
			Capabilities capabilities;
		};

		struct ElementRef {
			std::string ref;
		};

		inline
			picojson::value CustomToJson(const ElementRef& ref) {
			return JsonObject()
				.Set("ELEMENT", ref.ref)
				;
		}

		inline
			void CustomFromJson(const picojson::value& value, ElementRef& result) {
			WEBDRIVER_CHECK(value.is<picojson::object>(), "ElementRef is not an object");
			result.ref = FromJson<std::string>(value.get("ELEMENT"));
			if (result.ref == "null") {
				std::stringstream element(value.serialize());
				std::string segment;
				std::vector<std::string> strArr;
				while (std::getline(element, segment, ':')) {
					segment.erase(std::remove(segment.begin(), segment.end(), '{'), segment.end());
					segment.erase(std::remove(segment.begin(), segment.end(), '"'), segment.end());
					segment.erase(std::remove(segment.begin(), segment.end(), '}'), segment.end());
					strArr.push_back(segment);
				}
				if (strArr.size() >= 1) {
					std::stringstream ss;
					ss << "{\"ELEMENT\":" << "\"" << strArr[1] << "\"}";
					picojson::value jSon;
					picojson::parse(jSon, ss);
					result.ref = FromJson<std::string>(jSon.get("ELEMENT"));
				}
			}
		}

		inline
			void CustomFromJson(const picojson::value& value, SessionRef& result) {
			WEBDRIVER_CHECK(value.is<picojson::object>(), "Session information is not an object");
			result.id = value.get("sessionId").to_str();
			if (value.get("capabilities").is<picojson::object>())
				result.capabilities = Capabilities(value.get("capabilities").get<picojson::object>());
		}

	} 
} 

#endif
