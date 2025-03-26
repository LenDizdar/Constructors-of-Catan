#include "RandomBoard.h"
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include "Builder.h"
#include "FairDice.h"
#include "LoadedDice.h"
#include "Dice.h"

int main (int argc, char* argv[]) {

    // Default seed
    unsigned seed = 12345;

    //Handling command line arguments
    for (int i = 0; i < argc; i++) {

        std::string arg = argv[i];
        
        if (arg == "-seed") {

            seed = std::stoi(argv[i + 1]);

        }

    }

    RandomBoard b = RandomBoard(seed);

    std::cout << b.getDesc() << std::endl;

}

