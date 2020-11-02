#ifndef DETAIL_FACTORIES_H
#define DETAIL_FACTORIES_H

#include "shared.h"
#include <string>

namespace webdriverG {

	class Element;

	namespace detail {

		class Finder;
		class Resource;

		struct IFinderFactory {
			virtual Finder MakeFinder(const Shared<Resource>& context) = 0;
			virtual ~IFinderFactory() {}

		};

		struct IElementFactory {
			virtual Element MakeElement(const std::string& id) = 0;
			virtual ~IElementFactory() {}
		};

	} // namespace detail
}

#endif
