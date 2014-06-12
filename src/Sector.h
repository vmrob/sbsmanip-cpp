#pragma once

#include "Entity.h"

class Sector {
public:
	Sector(pugi::xml_node sectorRoot);

	size_t entityCount(int entityType = kEntityTypeAll) const;

	template <typename Pred, class = decltype(std::declval<Pred>().operator()(Entity()))>
	size_t entityCount(Pred&& predicate) const {
		size_t total = 0;
		
		// TODO: make predicate operate on Entity class, not pugi::xml_node
		for (auto&& sectorObject : _sectorObjects.children("MyObjectBuilder_EntityBase")) {
			if (predicate(Entity(sectorObject))) {
				++total;
			}
		}
	
		return total;
	}

	class Iterator
		: public boost::iterator_facade<
			Iterator,
			Entity,
			std::bidirectional_iterator_tag
		>
	{
		public:
			Iterator() = default;
			Iterator(Sector* sector, Entity _entity, std::function<bool(const Entity&)> filter);

		private:
			friend class boost::iterator_core_access;

			const Entity& dereference() const { return _entity; }

			bool equal(const Iterator& rhs) const {
				return _entity == rhs._entity
					&& _sector == rhs._sector;
			}

			void increment();
			void decrement();

			std::function<bool(const Entity&)> _filter;

			Sector* _sector = nullptr;
			Entity _entity;
	};


private:
	pugi::xml_node _sectorRoot;
	pugi::xml_node _sectorObjects;
};