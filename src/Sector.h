#pragma once

#include <pugixml.hpp>
#include "Entity.h"

class Sector {
public:
	Sector(pugi::xml_node sectorRoot);

	size_t entityCount(int type = kEntityTypeAll) const;


private:
	pugi::xml_node _sectorRoot;
	pugi::xml_node _sectorObjects;

};