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

#include <iostream>
#include <string>
#include <fstream>

#include "triplet_challenge.h"

constexpr auto MAX_BUFFER = 2 * 1024 * 1024; // 2 MiB

int main(int argc, char* argv[]) {
    // Ensure correct arguments
    if (argc < 2) {
        std::cerr << "Missing input file. e.g. " << argv[0] << " file.txt\n";
        exit(-1);
    }

    // Open file
    std::string filename{argv[1]};
    std::cerr << "Opening filename " << filename << "\n";
    std::ifstream fstream{filename, std::ios::in};
    if (!fstream.is_open()) {
        std::cerr << "Error reading file " << filename << "\n";
        return -1;
    }

    // Calculate file size
    const auto start = fstream.tellg();
    fstream.seekg(0, std::ios::end);
    const auto fileSize = fstream.tellg() - start;
    fstream.seekg(0, std::ios::beg);

    if (fileSize > MAX_BUFFER) {
        std::cerr << "The file size has " << fileSize << " bytes, which is greater than the maximum supported buffer "
                     "size of " << MAX_BUFFER << " bytes. Please recompile using a bigger MAX_BUFFER value.\n";
        return -1;
    }

    // Read whole file into a buffer
    char buffer[MAX_BUFFER];
    std::cerr << "File size: " << fileSize << " bytes\n";
    fstream.read(buffer, fileSize);

    auto triplets = calculateTriplets(buffer);
    for (const auto& triplet : triplets) {
        std::cout << triplet.words << " - " << triplet.count << "\n";
    }

    return 0;
}
