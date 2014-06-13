#include "pch.h"

#include "Sector.h"

Sector::Sector(pugi::xml_node sectorRoot)
	: _sectorRoot(sectorRoot)
	, _sectorObjects(_sectorRoot.child("SectorObjects"))
{

}

#include <iostream>

Sector::Iterator::Iterator(const Sector* sector, Entity entity, std::function<bool(const Entity&)> filter)
	: _filter(filter)
	, _sector(sector)
	, _entity(entity)
{
	if (!_filter(_entity)) {
		increment();
	}
}

void Sector::Iterator::increment() {
	do {
		_entity = _entity.node().next_sibling();
	} while (_entity.node() && !_filter(_entity));
}

void Sector::Iterator::decrement() {
	do {
		_entity = _entity.node().previous_sibling();
	} while (_entity.node() && !_filter(_entity));
}

Sector::Iterator Sector::begin(std::function<bool(const Entity&)> filter) const {
	return Iterator(this, _sectorObjects.first_child(), filter);
};

Sector::Iterator Sector::begin(int entityType) const {
	return Iterator(this, _sectorObjects.first_child(), [=](Entity e) { return entityType & e.type(); });
}

Sector::Iterator Sector::end() const {
	return Iterator(this, pugi::xml_node());
};

void Sector::erase(const Iterator first, const Iterator last) {
	for (auto it = first; it != last; ++it) {
		_sectorObjects.remove_child(it->node());
	}
}

Sector::Iterator Sector::find(Entity::Id id) const {
	for (auto it = begin(); it != end(); ++it) {
		if (it->id() == id) {
			return it;
		}
	}
	return end();
}