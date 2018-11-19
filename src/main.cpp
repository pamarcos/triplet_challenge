#include <iostream>
#include <string>
#include <fstream>

#include "triplet_challenge.h"

constexpr auto MAX_BUFFER = 10 * 1024 * 1024; // 10 MiB

int main(int argc, char* argv[])
{
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
        exit(-1);
    }

    // Calculate file size
    const auto start = fstream.tellg();
    fstream.seekg(0, std::ios::end);
    const auto fileSize = fstream.tellg() - start;
    fstream.seekg(0, std::ios::beg);

    // Read whole file into a buffer
    char buffer[fileSize];
    std::cerr << "File size: " << fileSize << " bytes\n";
    fstream.read(buffer, fileSize);

    auto triplet = getTriplet(buffer);
    for (const auto& word : triplet) {
        std::cout << word.word << " - " << word.number << "\n";
    }

    return 0;
}
