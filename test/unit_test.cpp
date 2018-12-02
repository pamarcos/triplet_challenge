/**
 * triplet_challenge is an application that extracts the top 3 triplet words of a file
 *
 * Copyright (C) 2018 Pablo Marcos Oltra
 *
 * This file is part of gencc.
 *
 * gencc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * gencc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gencc.  If not, see <http://www.gnu.org/licenses/>.
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

TEST_CASE("get next word", "[utility]") {
    std::string word{"foo"};
    std::string_view buffer{"this\t\n?is.=)a{small}$%test   .\n"};
    std::size_t offset = 0;

    auto getNextWordTest = [&](const std::string& testWord, std::size_t testOffset) {
        offset += getNextWord(buffer.substr(offset), word);
        REQUIRE(word == testWord);
        REQUIRE(offset == testOffset);
    };

    getNextWordTest("this", 7);
    getNextWordTest("is", 12);
    getNextWordTest("a", 14);
    getNextWordTest("small", 22);
    getNextWordTest("test", 31);
    REQUIRE(offset == buffer.size());

    buffer = "yet another test";
    offset = 0;
    getNextWordTest("yet", 4);
    getNextWordTest("another", 12);
    getNextWordTest("test", 16);
    REQUIRE(offset == buffer.size());
}

TEST_CASE("get triplet index", "[utility") {
    REQUIRE(getTripletIndex(0, 0) == 0);
    REQUIRE(getTripletIndex(0, 1) == 1);
    REQUIRE(getTripletIndex(0, 2) == 2);
    REQUIRE(getTripletIndex(0, 3) == 0);
    REQUIRE(getTripletIndex(0, 4) == 1);
    REQUIRE(getTripletIndex(0, 5) == 2);
    REQUIRE(getTripletIndex(0, -1) == 2);
    REQUIRE(getTripletIndex(0, -2) == 1);
    REQUIRE(getTripletIndex(0, -3) == 0);
    REQUIRE(getTripletIndex(0, -4) == 2);
    REQUIRE(getTripletIndex(0, -5) == 1);

    REQUIRE(getTripletIndex(2, 0) == 2);
    REQUIRE(getTripletIndex(2, 1) == 0);
    REQUIRE(getTripletIndex(2, 2) == 1);
    REQUIRE(getTripletIndex(2, 3) == 2);
    REQUIRE(getTripletIndex(2, 4) == 0);
    REQUIRE(getTripletIndex(2, 5) == 1);
    REQUIRE(getTripletIndex(2, -1) == 1);
    REQUIRE(getTripletIndex(2, -2) == 0);
    REQUIRE(getTripletIndex(2, -3) == 2);
    REQUIRE(getTripletIndex(2, -4) == 1);
    REQUIRE(getTripletIndex(2, -5) == 0);
}

TEST_CASE("calculate triplet", "[triplet]") {
    auto result = calculateTriplets("foo!?  bar!??? ye?!!. foo bar ye foo bar ye!?!?!?!:: . This is this foo bar ye bar "
                                    "that this bar ye foo");
    REQUIRE(result[0].words == "foo bar ye");
    REQUIRE(result[0].count == 4);
    REQUIRE(result[1].words == "bar ye foo");
    REQUIRE(result[1].count == 3);
    REQUIRE(result[2].words == "ye foo bar");
    REQUIRE(result[2].count == 2);
}
