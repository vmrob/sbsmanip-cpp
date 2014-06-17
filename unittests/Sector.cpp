#include <tinytest.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "../src/pch.h"
#include "../src/SbsFile.h"

static boost::filesystem::path gSupportDir("unittests/support");
static boost::filesystem::path gSandboxSbs("unittests/support/SANDBOX_0_0_0_.sbs");
static boost::filesystem::path gCubeBlocksSbc("unittests/support/CubeBlocks.sbc");
static boost::filesystem::path gRespawnShipSbc("unittests/support/RespawnShip.sbc");

TEST_SUITE("Sector") {

	SETUP() {
		CHECK_ESSENTIAL(boost::filesystem::exists(gSupportDir));
		CHECK_ESSENTIAL(boost::filesystem::is_directory(gSupportDir));

		CHECK_ESSENTIAL(boost::filesystem::exists(gSandboxSbs));
		CHECK_ESSENTIAL(boost::filesystem::is_regular_file(gSandboxSbs));

		CHECK_ESSENTIAL(boost::filesystem::exists(gCubeBlocksSbc));
		CHECK_ESSENTIAL(boost::filesystem::is_regular_file(gCubeBlocksSbc));

		CHECK_ESSENTIAL(boost::filesystem::exists(gRespawnShipSbc));
		CHECK_ESSENTIAL(boost::filesystem::is_regular_file(gRespawnShipSbc));
	};

	TEST("EntityCount") {
		boost::filesystem::ifstream f(gSandboxSbs);

		sbsmanip::SbsFile sbs;
		CHECK_NO_EXCEPTION(sbs = sbsmanip::SbsFile(f));

		auto sector = sbs.sector();

		CHECK(sector.entityCount(sbsmanip::kEntityTypeCubeGrid) == 20);
		CHECK(sector.entityCount(sbsmanip::kEntityTypeVoxelMap) == 72);
		CHECK(sector.entityCount(sbsmanip::kEntityTypeFloatingObject) == 10);
		CHECK(sector.entityCount(sbsmanip::kEntityTypeAll) == 102);
		CHECK(sector.entityCount(sbsmanip::kEntityTypeNone) == 0);

		CHECK(sector.entityCount(sbsmanip::kEntityTypeVoxelMap | sbsmanip::kEntityTypeFloatingObject) == 82);

		CHECK(sector.entityCount() == 102);

		// Lambda predicates
		CHECK(sector.entityCount([](sbsmanip::Entity e) { return true; }) == 102);
		CHECK(sector.entityCount([](sbsmanip::Entity e) { return e.type() == sbsmanip::kEntityTypeCubeGrid; }) == 20);
		CHECK(sector.entityCount([](sbsmanip::Entity e) { return e.id() == -1585641296703617821; }) == 1);
	};

	TEST("Find") {
		boost::filesystem::ifstream f(gSandboxSbs);

		sbsmanip::SbsFile sbs;
		CHECK_NO_EXCEPTION(sbs = sbsmanip::SbsFile(f));

		auto sector = sbs.sector();

		auto it = sector.find(-1585641296703617821);

		CHECK_ESSENTIAL(it != sector.end());

		CHECK(it->id() == -1585641296703617821);
		CHECK(it->type() == sbsmanip::kEntityTypeVoxelMap);
	};

	TEST("Iterators") {
		boost::filesystem::ifstream f(gSandboxSbs);

		sbsmanip::SbsFile sbs;
		CHECK_NO_EXCEPTION(sbs = sbsmanip::SbsFile(f));

		auto sector = sbs.sector();

		CHECK(std::distance(sector.begin(), sector.end()) == 102);
		CHECK(std::distance(sector.begin([](sbsmanip::Entity e) { return e.type() == sbsmanip::kEntityTypeCubeGrid; }), sector.end()) == 20);
		CHECK(std::distance(sector.begin(sbsmanip::kEntityTypeCubeGrid), sector.end()) == 20);
		CHECK(std::distance(sector.begin(sbsmanip::kEntityTypeCubeGrid | sbsmanip::kEntityTypeVoxelMap), sector.end()) == 92);
	};

	TEST("Erase") {
		boost::filesystem::ifstream f(gSandboxSbs);

		sbsmanip::SbsFile sbs;
		CHECK_NO_EXCEPTION(sbs = sbsmanip::SbsFile(f));

		auto sector = sbs.sector();
		
		CHECK(sector.entityCount() == 102);
		CHECK(sector.entityCount(sbsmanip::kEntityTypeCubeGrid) == 20);

		sector.erase(sector.begin(sbsmanip::kEntityTypeCubeGrid), sector.end());

		CHECK(sector.entityCount() == 82);

		auto it = sector.find(-1585641296703617821);
		CHECK_ESSENTIAL(it != sector.end());

		sector.erase(it);

		CHECK(sector.entityCount() == 81);
	};

	TEST("Interesting tricks") {
		boost::filesystem::ifstream f(gSandboxSbs);

		sbsmanip::SbsFile sbs;
		CHECK_NO_EXCEPTION(sbs = sbsmanip::SbsFile(f));

		auto sector = sbs.sector();
		
		CHECK(sector.entityCount() == 102);
		CHECK(sector.entityCount(sbsmanip::kEntityTypeCubeGrid) == 20);

		sector.erase(sector.begin(~sbsmanip::kEntityTypeCubeGrid), sector.end());

		CHECK(sector.entityCount() == 20);
	};

};