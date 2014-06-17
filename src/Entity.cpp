#include "pch.h"

#include "Entity.h"

namespace sbsmanip {

EntityType EntityTypeObjectBuilder(const char* objectBuilderStr) {
	return !strcmp(objectBuilderStr, "MyObjectBuilder_CubeGrid")       ? kEntityTypeCubeGrid :
	       !strcmp(objectBuilderStr, "MyObjectBuilder_VoxelMap")       ? kEntityTypeVoxelMap :
	       !strcmp(objectBuilderStr, "MyObjectBuilder_FloatingObject") ? kEntityTypeFloatingObject :
	       !strcmp(objectBuilderStr, "MyObjectBuilder_Character")      ? kEntityTypeCharacter :
	       !strcmp(objectBuilderStr, "MyObjectBuilder_Meteor")         ? kEntityTypeMeteor :
	       kEntityTypeNone;
}

Entity::Entity(pugi::xml_node node)
	: _node(node)
{
	// init only
}

Entity::Id Entity::id() const {
	if (_node) {
		return std::atoll(_node.child_value("EntityId"));	
	}
	return Id();
}

EntityType Entity::type() const {
	if (_node) {
		return EntityTypeObjectBuilder(_node.attribute("xsi:type").value());	
	}
	return kEntityTypeNone;
}

double Entity::xPosition() const {
	return _node.child("PositionAndOrientation").child("Position").attribute("x").as_double();
}

double Entity::yPosition() const {
	return _node.child("PositionAndOrientation").child("Position").attribute("y").as_double();
}

double Entity::zPosition() const {
	return _node.child("PositionAndOrientation").child("Position").attribute("z").as_double();
}

} // namespace sbsmanip