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

#include <iostream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "triplet_challenge.h"

int main(int argc, char* argv[]) {
    // Ensure correct arguments
    if (argc < 2) {
        std::cerr << "Missing input file. e.g. " << argv[0] << " file.txt\n";
        exit(-1);
    }

    // Open file
    std::string filename{argv[1]};
    std::cerr << "Opening filename " << filename << "\n";
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error reading file " << filename << "\n";
        return -1;
    }

    // Get the size
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        std::cerr << "Error getting stat of file " << filename << "\n";
        return -1;
    }
    std::cerr << "File size: " << sb.st_size << " bytes\n";

    // map the whole file into virtual memory. Let's delegate the implementation of reading in chunks to the OS
    void* buffer = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    auto triplets = calculateTriplets(static_cast<char*>(buffer));
    for (const auto& triplet : triplets) {
        std::cout << triplet.words << " - " << triplet.count << "\n";
    }

    munmap(buffer, sb.st_size);

    return 0;
}
