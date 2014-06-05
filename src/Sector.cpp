#include "Sector.h"

Sector::Sector(pugi::xml_node sectorRoot)
	: _sectorRoot(sectorRoot)
	, _sectorObjects(_sectorRoot.child("SectorObjects"))
{

}

#include <iostream>

size_t Sector::entityCount(int type) const {
	size_t total = 0;

	for (auto&& sectorObject : _sectorObjects.children("MyObjectBuilder_EntityBase")) {
		if (type & EntityTypeObjectBuilder(sectorObject.attribute("xsi:type").value())) {
			++total;
		}
	}

	return total;
}