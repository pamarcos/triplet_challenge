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

#pragma once

#include <string>
#include <array>

// API
struct Triplet {
    std::string words;
    std::size_t count = 0;

    bool operator>(const Triplet& other) const {
        return count > other.count;
    }

    bool operator==(const Triplet& other) const {
        return words == other.words;
    }
};

using TripletResult = std::array<Triplet, 3>;

TripletResult calculateTriplets(std::string_view buffer);

// Internal stuff to unit test
enum class FindType {
    FIRST_CHARACTER,
    FIRST_NON_CHARACTER
};

bool shouldSkipCharacter(const char c);
std::size_t findFirstCharacter(std::string_view buffer);
std::size_t findFirstNonCharacter(std::string_view buffer);
std::size_t getNextWord(std::string_view buffer, std::string& word);
std::size_t getTripletIndex(ssize_t firstWord, ssize_t offset);
