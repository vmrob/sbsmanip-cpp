#include <tinytest.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "../src/XmlDocument.h"

TEST_SUITE("XmlDocument") {

	TEST("Read") {
		boost::filesystem::path support("unittests/support");
		CHECK_ESSENTIAL(boost::filesystem::exists(support));
		CHECK_ESSENTIAL(boost::filesystem::is_directory(support));

		auto sandbox = support / "SANDBOX_0_0_0_.sbs";
		CHECK_ESSENTIAL(boost::filesystem::exists(sandbox));
		CHECK_ESSENTIAL(boost::filesystem::is_regular_file(sandbox));

		boost::filesystem::ifstream f(sandbox);

		CHECK_NO_EXCEPTION(XmlDocument(f));
	};

};