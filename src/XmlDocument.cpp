#include "pch.h"

#include "XmlDocument.h"

namespace sbsmanip {

XmlDocument::XmlDocument(std::istream& stream) {
	pugi::xml_parse_result result = _xml->load(stream);

	if (!result) {
		throw std::runtime_error("XML parsed with errors");
	}
}

} // namespace sbsmanip