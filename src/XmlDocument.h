#include <istream>
#include <pugixml.hpp>

class XmlDocument {
public:
	XmlDocument(std::istream& stream);

private:
	pugi::xml_document _xml;
};