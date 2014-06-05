#pragma once

#include "XmlDocument.h"
#include "Sector.h"

class SbsFile : public XmlDocument {
public:
	using XmlDocument::XmlDocument;

	Sector sector();
};