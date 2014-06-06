#pragma once

enum EntityType : uint32_t {
	kEntityTypeNone           = 0x0,
	kEntityTypeCubeGrid       = 0x1,
	kEntityTypeVoxelMap       = 0x2,
	kEntityTypeFloatingObject = 0x4,
	kEntityTypeCharacter      = 0x8,
	kEntityTypeMeteor         = 0x10,

	kEntityTypeAll            = std::numeric_limits<uint32_t>::max(),
};

constexpr const char* EntityTypeObjectBuilderStr(EntityType type) {
	return type == kEntityTypeCubeGrid       ? "MyObjectBuilder_CubeGrid" :
	       type == kEntityTypeVoxelMap       ? "MyObjectBuilder_VoxelMap" :
	       type == kEntityTypeFloatingObject ? "MyObjectBuilder_FloatingObject" :
	       type == kEntityTypeCharacter      ? "MyObjectBuilder_Character" :
	       type == kEntityTypeMeteor         ? "MyObjectBuilder_Meteor" :
	       "[unknown ObjectBuilder type]";
}

EntityType EntityTypeObjectBuilder(const char* objectBuilderStr);

typedef std::string EntityId; // hashable/comparable value

class Entity {
public:
	static EntityId Id(const pugi::xml_node& node);
};

typedef std::shared_ptr<const Entity> ConstEntityRef;
typedef std::shared_ptr<Entity> EntityRef;