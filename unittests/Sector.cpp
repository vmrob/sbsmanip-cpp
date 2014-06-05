#include <tinytest.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "../src/SbsFile.h"

TEST_SUITE("Sector") {

	TEST("EntityCount") {
		boost::filesystem::path support("unittests/support");
		CHECK_ESSENTIAL(boost::filesystem::exists(support));
		CHECK_ESSENTIAL(boost::filesystem::is_directory(support));

		auto sandbox = support / "SANDBOX_0_0_0_.sbs";
		CHECK_ESSENTIAL(boost::filesystem::exists(sandbox));
		CHECK_ESSENTIAL(boost::filesystem::is_regular_file(sandbox));

		boost::filesystem::ifstream f(sandbox);

		SbsFile sbs;
		CHECK_NO_EXCEPTION(sbs = SbsFile(f));

		auto sector = sbs.sector();

		CHECK(sector.entityCount(kEntityTypeCubeGrid) == 20);
		CHECK(sector.entityCount(kEntityTypeVoxelMap) == 72);
		CHECK(sector.entityCount(kEntityTypeFloatingObject) == 10);
		CHECK(sector.entityCount(kEntityTypeAll) == 102);
		CHECK(sector.entityCount(kEntityTypeNone) == 0);

		CHECK(sector.entityCount(kEntityTypeVoxelMap | kEntityTypeFloatingObject) == 82);

		CHECK(sector.entityCount() == 102);
	};

};