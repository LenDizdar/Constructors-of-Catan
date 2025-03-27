#include "RandomBoard.h"
#include "LoadedBoard.h"
#include <iostream>
#include <random>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "Builder.h"
#include "FairDice.h"
#include "LoadedDice.h"
#include "Dice.h"
#include "Goose.h"

using namespace std;

void addBuilder(string colour, Dice* die, string fileInput, vector<Builder> &builders) {

    builders.emplace_back(Builder("Blue", die));
    istringstream iss{fileInput};

}

int main (int argc, char* argv[]) {

    unsigned seed = 12345; // Default seed
    string fileName = "layout.txt"; // Default file name
    bool loadBoard = false;
    bool randomBoard = false;
    bool fullSave = false;

    // Handling command line arguments
    for (int i = 1; i < argc; i++) {

        string arg = argv[i];
        
        if (arg == "-seed") {

            seed = stoi(argv[i + 1]);
            ++i;

        } else if (arg == "-board") {

            fileName = argv[i + 1];
            loadBoard = true;
            ++i;

        } else if (arg == "-random-board") {

            randomBoard = true;

        } else if (arg == "-load") {

            fileName = argv[i + 1];
            fullSave = true;
            loadBoard = true;
            ++i;

        }

    }

    // Creating Board and Builders based on command line input
    Board *b = nullptr;
    unique_ptr<Dice> loaded = make_unique<Dice>(LoadedDice());
    unique_ptr<Dice> fair = make_unique<Dice>(FairDice(seed));
    vector<Builder> builders;

    if (loadBoard) {

        ifstream file{fileName};
        string s;
        for (int i = 0; i < 6; ++i) { getline(file, s); }
        addBuilder("Blue", loaded.get(), s, builders);

    } else if (randomBoard) {

        b = new RandomBoard(seed);
        builders.emplace_back(Builder("Blue", loaded.get()));
        builders.emplace_back(Builder("Red", loaded.get()));
        builders.emplace_back(Builder("Orange", loaded.get()));
        builders.emplace_back(Builder("Yellow", loaded.get()));

    } else {

        // Default file open
        ifstream file{fileName};
        string s;
        getline(file, s);
        b = new LoadedBoard(s);
        builders.emplace_back(Builder("Blue", loaded.get()));
        builders.emplace_back(Builder("Red", loaded.get()));
        builders.emplace_back(Builder("Orange", loaded.get()));
        builders.emplace_back(Builder("Yellow", loaded.get()));

    }

    cout << b->getDesc() << endl;

}

