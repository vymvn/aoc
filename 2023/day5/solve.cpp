#include <cstdlib>
#include <iostream>
#include <fstream>

int main (int argc, char *argv[]) {
    
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename = argv[1];
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error: cannot open file '" << filename << "'" << std::endl;
        return EXIT_FAILURE;
    }

    std::string line;

    while (std::getline(file, line)) {
        // process line
    }

    return EXIT_SUCCESS;
}
