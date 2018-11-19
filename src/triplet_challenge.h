#pragma once

#include <string>
#include <array>

struct Word {
    std::string word;
    int number = 0;
};

using TripletResult = std::array<Word, 3>;

TripletResult getTriplet(std::string_view buffer);
