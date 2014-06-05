#pragma once

#include <istream>
#include <memory>
#include <pugixml.hpp>

#include "utility.h"

class XmlDocument {
public:
	XmlDocument() = default;
	XmlDocument(std::istream& stream);


protected:
	inline pugi::xml_document& _root() { return *_xml; }

private:
	std::unique_ptr<pugi::xml_document> _xml = std::make_unique<pugi::xml_document>();
};