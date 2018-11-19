#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "triplet_challenge.h"

TEST_CASE("get triplet works", "[triplet]")
{
    auto result = getTriplet("this is a test");
}
