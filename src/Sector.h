#pragma once

#include "Entity.h"

namespace sbsmanip {

class Sector {
public:
	Sector(pugi::xml_node sectorRoot);

	inline size_t entityCount(int entityType = kEntityTypeAll) const {
		return entityCount([=](Entity e) { return entityType & e.type(); });
	}

	template <typename Pred, class = decltype(std::declval<Pred>().operator()(Entity()))>
	size_t entityCount(Pred&& predicate) const {
		return std::count_if(begin(), end(), predicate);
	}

	class Iterator
		: public boost::iterator_facade<
			Iterator,
			Entity,
			std::bidirectional_iterator_tag,
			const Entity&
		>
	{
		public:
			Iterator() = default;
			Iterator(
				const Sector* sector,
				Entity _entity,
				std::function<bool(const Entity&)> filter = [](auto e) { return true; }
			);

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

			const Sector* _sector = nullptr;
			Entity _entity;
	};

	Iterator begin(std::function<bool(const Entity&)> filter = [](auto e) { return true; }) const;
	Iterator begin(int entityType) const;
	Iterator end() const;

	void erase(const Iterator first, const Iterator last);
	void erase(const Iterator it);

	Iterator find(Entity::Id id) const;

private:
	pugi::xml_node _sectorRoot;
	pugi::xml_node _sectorObjects;
};

} // namespace sbsmanip