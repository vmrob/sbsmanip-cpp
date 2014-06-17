#pragma once

namespace sbsmanip {

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

class Entity : public boost::totally_ordered<Entity> {
public:
	Entity(pugi::xml_node node = pugi::xml_node());

	typedef int64_t Id;

	// return value of 0 represents invalid stored id
	Id id() const;
	EntityType type() const;

	inline bool operator==(const Entity& rhs) const { return id() == rhs.id(); }
	inline bool operator< (const Entity& rhs) const { return id() <  rhs.id(); }

	pugi::xml_node node() const { return _node; }
private:
	pugi::xml_node _node;
};

typedef std::shared_ptr<const Entity> ConstEntityRef;
typedef std::shared_ptr<Entity> EntityRef;

} // namespace sbsmanip