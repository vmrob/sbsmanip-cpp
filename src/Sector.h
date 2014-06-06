#pragma once

#include "Entity.h"

class Sector {
public:
	Sector(pugi::xml_node sectorRoot);

	size_t entityCount(int entityType = kEntityTypeAll) const;

	template <typename Pred, class = decltype(std::declval<Pred>().operator()(std::declval<pugi::xml_node>()))>
	size_t entityCount(Pred&& predicate) const {
		size_t total = 0;
		
		// TODO: make predicate operate on Entity class, not pugi::xml_node
		for (auto&& sectorObject : _sectorObjects.children("MyObjectBuilder_EntityBase")) {
			if (predicate(sectorObject)) {
			//if (type & EntityTypeObjectBuilder(sectorObject.attribute("xsi:type").value())) {
				++total;
			}
		}
	
		return total;
	}

	class Iterator
		: public boost::iterator_facade<
			Iterator,
			EntityRef,
			std::bidirectional_iterator_tag
		>
	{
		public:
			Iterator() = default;
			Iterator(Sector* sector, EntityRef _entity, std::function<bool()> filter);

		private:
			friend class boost::iterator_core_access;

			static_assert(std::is_same<EntityRef&, reference>::value, "");

			const EntityRef& dereference() const { return _entity; }

			bool equal(const Iterator& rhs) const {
				return _entity == rhs._entity
					&& _sector == rhs._sector;
			}

			void increment();
			void decrement();

			std::function<bool()> _filter;

			Sector* _sector = nullptr;
			EntityRef _entity;
	};


private:
	pugi::xml_node _sectorRoot;
	pugi::xml_node _sectorObjects;

	std::unordered_map<EntityId, EntityRef> _entities; // entities mapped by id
};