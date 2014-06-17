#pragma once

#include "XmlDocument.h"
#include "Sector.h"

namespace sbsmanip {

class SbsFile : public XmlDocument {
public:
	using XmlDocument::XmlDocument;

	Sector sector();
};

} // namespace sbsmanip