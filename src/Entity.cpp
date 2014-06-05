#include "Entity.h"

EntityType EntityTypeObjectBuilder(const char* objectBuilderStr) {
	return !strcmp(objectBuilderStr, "MyObjectBuilder_CubeGrid")       ? kEntityTypeCubeGrid :
	       !strcmp(objectBuilderStr, "MyObjectBuilder_VoxelMap")       ? kEntityTypeVoxelMap :
	       !strcmp(objectBuilderStr, "MyObjectBuilder_FloatingObject") ? kEntityTypeFloatingObject :
	       !strcmp(objectBuilderStr, "MyObjectBuilder_Character")      ? kEntityTypeCharacter :
	       !strcmp(objectBuilderStr, "MyObjectBuilder_Meteor")         ? kEntityTypeMeteor :
	       kEntityTypeNone;
}