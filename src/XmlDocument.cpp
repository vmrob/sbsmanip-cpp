#include "pch.h"

#include "XmlDocument.h"
#include "utility.h"

namespace sbsmanip {

XmlDocument::XmlDocument(std::istream& stream) {
	pugi::xml_parse_result result = _xml->load(stream);

	if (!result) {
		throw std::runtime_error(Format(
			"XML parsed with errors:\n"
			"Error description: %s\n",
			result.description(), result.offset));
	}
}

} // namespace sbsmanip