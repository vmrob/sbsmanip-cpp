#include "pch.h"

#include "Sector.h"

Sector::Sector(pugi::xml_node sectorRoot)
	: _sectorRoot(sectorRoot)
	, _sectorObjects(_sectorRoot.child("SectorObjects"))
{

}

size_t Sector::entityCount(int entityType) const {
	size_t total = 0;
	
	// TODO: operate on Entity class, not pugi::xml_node
	for (auto&& sectorObject : _sectorObjects.children("MyObjectBuilder_EntityBase")) {
		if (entityType & EntityTypeObjectBuilder(sectorObject.attribute("xsi:type").value())) {
			++total;
		}
	}

	return total;
}

// Sector::Iterator::Iterator(Sector* sector, EntityRef _entity, std::function<bool()> filter) {

// }

// void Sector::Iterator::increment() {

// }

// void Sector::Iterator::decrement() {

// }
