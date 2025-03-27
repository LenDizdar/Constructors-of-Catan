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
#include <stdexcept>
#include <limits>

using namespace std;

void addBuilder(string colour, Dice* die, string fileInput, vector<Builder> &builders, Board *b) {

    builders.emplace_back(Builder(colour, die));
    istringstream iss{fileInput};

    // Adding Resources
    ResourceList toAdd;
    for (int i = 0; i < 5; ++i) {

        int num;
        iss >> num;
        toAdd.set(Resource(i), num);

    }
    builders.back().addResources(toAdd);

    //Adding roads
    string buffer;
    iss >> buffer;
    int index;

    while (iss >> index) {

        builders.back().buildRoad(&(b->getEdge(index)), true);

    }

    iss.clear();
    iss.ignore();

    // Adding buildings
    while (iss >> index) {

        string type;
        iss >> type;
        builders.back().buildRes(&(b->getVertex(index)), true);

        if (type == "H") {

            builders.back().improve(&(b->getVertex(index)), true);

        } else if (type == "T") {

            builders.back().improve(&(b->getVertex(index)), true);
            builders.back().improve(&(b->getVertex(index)), true);
            
        }

    }

}

constexpr auto max_size = numeric_limits<streamsize>::max();

template <typename T> T read_valid(bool (*valid)(T), string reprompt) {
    T input;
    cout << ">";
    while (!(cin >> input) || !valid(input)) {
        if (cin.eof()) {
            throw exception();
        }
        cin.clear();
        cin.ignore(max_size, '\n');
        cout << reprompt << ">";
    }
    return input;
}

bool validVertex(int in) {
    // bad magic numbers
    return 0 <= in && in <= 53;
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
            loadBoard = true;
            fullSave = true;
            ++i;

        }

    }

    // Creating Board and Builders based on command line input
    unique_ptr<Board> b;
    unique_ptr<Goose> goose = make_unique<Goose>(nullptr);
    unique_ptr<Dice> loaded = make_unique<LoadedDice>(LoadedDice());
    unique_ptr<Dice> fair = make_unique<FairDice>(FairDice(seed));
    vector<Builder> builders;
    unsigned curr_builder = 0;

    if (loadBoard && fullSave) {

        ifstream file{fileName};
        string turn, blue, red, orange, yellow, boardSave, gooseLoc;
        getline(file, turn);
        getline(file, blue);
        getline(file, red);
        getline(file, orange);
        getline(file, yellow);
        getline(file, boardSave);
        getline(file, gooseLoc);
        // curr_builder should be different, find where that colour is in builders.
        curr_builder = stoi(turn);
        b = make_unique<LoadedBoard>(boardSave);
        addBuilder("Blue", loaded.get(), blue, builders, &(*b));
        addBuilder("Red", loaded.get(), red, builders, &(*b));
        addBuilder("Orange", loaded.get(), orange, builders, &(*b));
        addBuilder("Yellow", loaded.get(), yellow, builders, &(*b));
        goose->move(b->getTile(stoi(gooseLoc)));

    }  else if (loadBoard || !randomBoard) {

        // Load only Board from file
        ifstream file{fileName};
        string s;
        getline(file, s);
        b = make_unique<LoadedBoard>(s);
        builders.emplace_back(Builder("Blue", loaded.get()));
        builders.emplace_back(Builder("Red", loaded.get()));
        builders.emplace_back(Builder("Orange", loaded.get()));
        builders.emplace_back(Builder("Yellow", loaded.get()));
        
    } else {

        // Random Board;
        b = make_unique<RandomBoard>(seed);
        builders.emplace_back(Builder("Blue", loaded.get()));
        builders.emplace_back(Builder("Red", loaded.get()));
        builders.emplace_back(Builder("Orange", loaded.get()));
        builders.emplace_back(Builder("Yellow", loaded.get()));

    }

    cout << b->getDesc() << endl;

    
    // Beginning of Game
    try {
        if (!fullSave) {

            int bSize = builders.size();
            bool firstRound = true;

            for (int i = 0; i >= 0; firstRound ? ++i : --i) {

                if (i == bSize) {
                    --i;
                    firstRound = false;
                } 

                cout << "Builder " << builders[i].getColour() << ", where do you want to build a basement?" << endl;
                while (!builders[i].buildRes(&b->getVertex(read_valid<int>(&validVertex, "You cannot build here.\n")), true)) {
                    cout << "You cannot build here." << endl;
                }
            }
        }

        while (true) {
            cout << "Builder " << builders[curr_builder].getColour() << "'s turn." << endl;
            curr_builder = (curr_builder + 1) % builders.size();
            // Break at end of first turn FOR TESTING
            if (curr_builder == builders.size() - 1) break;
        }

    } catch (...) {
        // save then terminate program due to EOF.
    }
}

