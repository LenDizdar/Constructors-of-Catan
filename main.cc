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

    unsigned seed = 12345; // Default seed
    std::string fileName = "layout.txt"; // Default file name
    bool loadBoard = false;
    bool randomBoard = false;

    // Handling command line arguments
    for (int i = 1; i < argc; i++) {

        std::string arg = argv[i];
        
        if (arg == "-seed") {

            seed = std::stoi(argv[i + 1]);
            ++i;

        } else if (arg == "-board") {

            fileName = argv[i + 1];
            loadBoard = true;
            ++i;

        } else if (arg == "-random-board") {

            randomBoard = true;

        } else if (arg == "-load") {

            loadBoard = true;

        }

    }

    // Creating Board based on command line input
    Board *b = nullptr;

    if (loadBoard) {

        // To implement

    } else if (randomBoard) {



    }

    //std::cout << b->getDesc() << std::endl;

}

