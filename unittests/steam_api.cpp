#include <tinytest.h>

#include "sbsmanip.h"

TEST_SUITE("Steam API") {

	TEST("SteamId") {
		CHECK(sbsmanip::GetSteamId(76561197968575517).get() == "Chet");
	};
	
};