#pragma once

#include "utility.h"

namespace sbsmanip {

class XmlDocument {
public:
	XmlDocument() = default;
	XmlDocument(std::istream& stream);

	inline pugi::xml_document& root() { return *_xml; }

private:
	std::unique_ptr<pugi::xml_document> _xml = std::make_unique<pugi::xml_document>();
};

} // namespace sbsmanip