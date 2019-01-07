/**
 * triplet_challenge is an application that extracts the top 3 triplet words of a file
 *
 * Copyright (C) 2018 Pablo Marcos Oltra
 *
 * This file is part of triplet_challenge.
 *
 * triplet_challenge is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * triplet_challenge is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with triplet_challenge.  If not, see <http://www.gnu.org/licenses/>.
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "triplet_challenge.h"

TEST_CASE("should skip a character", "[utility]") {
    REQUIRE(!shouldSkipCharacter('A'));
    REQUIRE(!shouldSkipCharacter('Z'));
    REQUIRE(!shouldSkipCharacter('a'));
    REQUIRE(!shouldSkipCharacter('z'));
    REQUIRE(!shouldSkipCharacter('0'));
    REQUIRE(!shouldSkipCharacter('9'));
    REQUIRE(!shouldSkipCharacter('\''));

    REQUIRE(shouldSkipCharacter(' '));
    REQUIRE(shouldSkipCharacter('\n'));
    REQUIRE(shouldSkipCharacter('?'));
    REQUIRE(shouldSkipCharacter('!'));
    REQUIRE(shouldSkipCharacter(';'));
    REQUIRE(shouldSkipCharacter('.'));
    REQUIRE(shouldSkipCharacter('-'));
    REQUIRE(shouldSkipCharacter('&'));
    REQUIRE(shouldSkipCharacter('<'));
}

TEST_CASE("find first character", "[utility]") {
    REQUIRE(findFirstCharacter("a?!¿b") == 0);
    REQUIRE(findFirstCharacter("Z1234") == 0);
    REQUIRE(findFirstCharacter("12-.3") == 0);
    REQUIRE(findFirstCharacter(" -?;.a'Z") == 5);
    REQUIRE(findFirstCharacter(" -?;.'aZ") == 5);
    REQUIRE(findFirstCharacter(" -?;.'") == 5);
    REQUIRE(findFirstCharacter("?!-.") == 4);
}

TEST_CASE("find first non character", "[utility]") {
    REQUIRE(findFirstNonCharacter("a?!¿b") == 1);
    REQUIRE(findFirstNonCharacter("Z1234") == 5);
    REQUIRE(findFirstNonCharacter("12-.3") == 2);
    REQUIRE(findFirstNonCharacter("aZv -?;.a'Z") == 3);
    REQUIRE(findFirstNonCharacter("1;f.'aZ") == 1);
    REQUIRE(findFirstNonCharacter("?;.'") == 0);
}

TEST_CASE("jump next word", "[utility]") {
    std::string_view buffer{"this\t\n?is.=)a{small}$%test   .\n"};
    std::size_t offset = 0;

    auto jumpNextWordTest = [&](std::size_t testOffset) {
        offset += jumpNextWord(buffer.substr(offset));
        REQUIRE(offset == testOffset);
    };

    jumpNextWordTest(7);
    jumpNextWordTest(12);
    jumpNextWordTest(14);
    jumpNextWordTest(22);
    jumpNextWordTest(31);
    REQUIRE(offset == buffer.size());

    buffer = "yet another test";
    offset = 0;
    jumpNextWordTest(4);
    jumpNextWordTest(12);
    jumpNextWordTest(16);
    REQUIRE(offset == buffer.size());
}

TEST_CASE("sanitize buffer", "[utility]") {
    char buffer[] = "ThiS.- SiMPlE. .*+-tESt";
    std::size_t numberOfWords = 12345;
    const auto length = sanitizeBuffer(buffer, sizeof(buffer) - 1, numberOfWords);
    REQUIRE(numberOfWords == 3);
    REQUIRE(length == 16);
    REQUIRE(std::string(buffer, length) == "this simple test");
}

TEST_CASE("calculate triplet", "[triplet]") {
    char buffer[] = "foo!?  bar!??? ye?!!. foo bar ye foo bar ye!?!?!?!:: . This is this foo bar ye bar "
                  "that this bar ye foo";
    auto result = calculateTriplets(buffer, sizeof(buffer) - 1);
    REQUIRE(result[0].words == "foo bar ye");
    REQUIRE(result[0].count == 4);
    REQUIRE(result[1].words == "bar ye foo");
    REQUIRE(result[1].count == 3);
    REQUIRE(result[2].words == "ye foo bar");
    REQUIRE(result[2].count == 2);
}
