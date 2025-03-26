#include "RandomBoard.h"
#include <iostream>
#include <random>

int main (int argc, char* argv[]) {

    unsigned seed = 12345;
    if (argc > 1) {
        seed = std::stoi(argv[1]);
    }
    RandomBoard b = RandomBoard(seed);

    std::cout << b.getDesc() << std::endl;

}

