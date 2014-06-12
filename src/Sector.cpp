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
		if (entityType & Entity(sectorObject).type()) {
			++total;
		}
	}

	return total;
}

Sector::Iterator::Iterator(Sector* sector, Entity entity, std::function<bool(const Entity&)> filter)
	: _filter(filter)
	, _sector(sector)
	, _entity(entity)
{
	// init only
}

// void Sector::Iterator::increment() {

// }

// void Sector::Iterator::decrement() {

// }
