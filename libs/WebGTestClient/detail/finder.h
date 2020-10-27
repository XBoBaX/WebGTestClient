#ifndef DETAIL_FINDER_H
#define DETAIL_FINDER_H

#include "shared.h"
#include "resource.h"
#include "factories.h"
#include "../by.h"
#include <vector>

namespace webdriver {

	class Element;

	namespace detail {

		class Finder { // copyable
		public:
			Finder(
				const Shared<Resource>& context,
				const Shared<IElementFactory>& factory
			);

			Element FindElement(const By& by) const;
			std::vector<Element> FindElements(const By& by) const;

		private:
			Shared<Resource> context_;
			Shared<IElementFactory> factory_;
		};

	} // namespace detail
} 

#include "finder.inl"

#endif
