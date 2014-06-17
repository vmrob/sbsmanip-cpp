#include <tinytest.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "sbsmanip.h"

static boost::filesystem::path gSandboxSbs("unittests/support/SANDBOX_0_0_0_.sbs");

TEST_SUITE("Entity") {

	SETUP() {
		CHECK_ESSENTIAL(boost::filesystem::exists(gSandboxSbs));
		CHECK_ESSENTIAL(boost::filesystem::is_regular_file(gSandboxSbs));
	};

	TEST("Attributes") {
		boost::filesystem::ifstream f(gSandboxSbs);

		sbsmanip::SbsFile sbs;
		CHECK_NO_EXCEPTION(sbs = sbsmanip::SbsFile(f));

		auto sector = sbs.sector();

		auto it = sector.find(-1585641296703617821);

		CHECK_ESSENTIAL(it != sector.end());

		CHECK(it->id() == -1585641296703617821);
		CHECK(it->type() == sbsmanip::kEntityTypeVoxelMap);

		CHECK(it->xPosition() == -1781.54041);
		CHECK(it->yPosition() == -2031.78015);
		CHECK(it->zPosition() == -1400.35547);
	};

};