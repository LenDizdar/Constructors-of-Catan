#include "RandomBoard.h"
#include "LoadedBoard.h"
#include <iostream>
#include <random>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "Builder.h"
#include "Basement.h"
#include "FairDice.h"
#include "LoadedDice.h"
#include "Dice.h"
#include "Goose.h"
#include <stdexcept>
#include <limits>
#include "ResourceList.h"

using namespace std;

void addBuilder(string colour, Dice* die, string fileInput, vector<Builder> &builders, Board *b, int& startingBuildings) {

    builders.emplace_back(colour, die);
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

        ++startingBuildings;

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

template <typename T> bool read_one_valid(bool (*valid)(T), T& ret) {
    cout << ">";
    if (!(cin >> ret) || !valid(ret)) {
        if (cin.eof()) {
            throw exception();
        }
        cin.clear();
        cin.ignore(max_size, '\n');
        return false;
    }
    return true;
}

bool validVertex(int in) {
    // bad magic numbers
    return 0 <= in && in <= 53;
}

bool validTurnBegin(string str) {
    return str == "load" || str == "fair" || str == "roll";
}

bool retTrue(string str) {
    return true;
}

bool yes_no(string str) {
    return str == "yes" || str == "no";
}

bool isValidResource(string str) {
    return str == "brick" || str == "energy" || str == "glass" ||
           str == "heat" || str == "wifi";
}

bool validTurnCmd(string str) {
    return str == "board" || str == "status" || str == "residences" ||
           str == "build-road" || str == "build-res" || str == "improve" ||
           str == "trade" || str == "next" || str == "save" || str == "help";
}

bool validEdge(int in) {
    return 0 <= in && in <= 71;
}

bool validTile(int in) {
    return 0 <= in && in <= 18;
}

int main (int argc, char* argv[]) {

    unsigned seed = 12345; // Default seed
    string fileName = "layout.txt"; // Default file name
    bool loadBoard = false;
    bool randomBoard = false;
    bool fullSave = false;
    int startingBuildings = 0;

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

    default_random_engine rand{seed};
    unique_ptr<Board> b;
    unique_ptr<Goose> goose = make_unique<Goose>(nullptr);
    unique_ptr<Dice> loaded = make_unique<LoadedDice>(LoadedDice());
    unique_ptr<Dice> fair = make_unique<FairDice>(FairDice(seed));
    vector<Builder> builders;
    builders.reserve(4);
    unsigned turn = 0;
    bool gameBegun = true;
    string continueGame = "no";

    // If eof exception is thrown, the game with exit and save to a file
    try {
        
        // A new game will reset this loop
        while (true) {

            // Setting up the board
            if (loadBoard && fullSave) {

                ifstream file{fileName};
                string turn_str, blue, red, orange, yellow, boardSave, gooseLoc;
                getline(file, turn_str);
                getline(file, blue);
                getline(file, red);
                getline(file, orange);
                getline(file, yellow);
                getline(file, boardSave);
                getline(file, gooseLoc);
                b = make_unique<LoadedBoard>(boardSave);
                addBuilder("Blue", loaded.get(), blue, builders, &(*b), startingBuildings);
                addBuilder("Red", loaded.get(), red, builders, &(*b), startingBuildings);
                addBuilder("Orange", loaded.get(), orange, builders, &(*b), startingBuildings);
                addBuilder("Yellow", loaded.get(), yellow, builders, &(*b), startingBuildings);
                for (int i = 0; i < static_cast<int>(builders.size()); ++i) {
                    if (builders[i].getColour() == turn_str) {
                        turn = i;
                        break;
                    }
                }
                if (stoi(gooseLoc) != -1) (goose->move(b->getTile(stoi(gooseLoc))));
        
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
                b = make_unique<RandomBoard>(rand);
                builders.emplace_back(Builder("Blue", loaded.get()));
                builders.emplace_back(Builder("Red", loaded.get()));
                builders.emplace_back(Builder("Orange", loaded.get()));
                builders.emplace_back(Builder("Yellow", loaded.get()));
        
            }
            cout << b->getDesc() << endl;
            // ~Setting up the Board

            // Beginning of Game phase
            if (startingBuildings < static_cast<int>(builders.size()) * 2) {
                gameBegun = false;
                int bSize = builders.size();
                bool firstRound = true;

                if (startingBuildings >= bSize) {
                    startingBuildings = 2 * bSize - (startingBuildings) - 1;
                    firstRound = false;
                }

                for (int i = startingBuildings; i >= 0; firstRound ? ++i : --i) {

                    if (i == bSize) {
                        --i;
                        firstRound = false;
                    } 

                    cout << "Builder " << builders[i].getColour() << ", where do you want to build a basement?" << endl;
                    while (!builders[i].buildRes(&b->getVertex(read_valid<int>(&validVertex, "You cannot build here.\n")), true)) {
                        cout << "You cannot build here." << endl;
                    }
                }

                cout << b->getDesc() << endl;
                gameBegun = true;
            } 
            // ~Beginning of Game phase
            
            // Game loop
            while (true) {
                Builder& curr_builder = builders[turn];
                cout << "Builder " << curr_builder.getColour() << "'s turn." << endl;
                
                // Beginning of turn phase

                vector<ResourceList> prevResources;
                for (auto& builder : builders) {
                    prevResources.emplace_back(builder.getHand());
                }

                while (true) {
                    string dieAction = read_valid<string>(&validTurnBegin, "Invalid command.\nTry 'load', 'fair', or 'roll'.\n");
                    if (dieAction == "load") {
                        curr_builder.setDie(&(*loaded));
                        cout << "Dice loaded." << endl;
                        continue;
                    } else if (dieAction == "fair") {
                        curr_builder.setDie(&(*fair));
                        cout << "Dice fair." << endl;
                        continue;
                    } else {
                        // roll!
                        int theRoll = curr_builder.roll();
                        cout << "Rolled a " << theRoll << "!" << endl;
                        if (theRoll == 7) {
                            // Goose!
                            for (auto& builder : builders) {
                                cout << builder.getColour() << " loses:" << endl;
				cout << builder.halfResources();
                            }
                            cout << "Choose where to place the GEESE." << endl;
                            while (true) {
                                int moveTile = read_valid<int>(&validTile, "Please choose a valid tile for placing the GEESE.\n");
                                if (moveTile == goose->getIndex()) {
                                    cout << "The GEESE are already at that tile." << endl << "Please choose a valid tile for placing the GEESE." << endl;
                                } else {

                                    goose->move(b->getTile(moveTile));
                                    
                                    std::vector<Builder*> possibleVictims = b->getTile(moveTile)->getBuildersOnTile();

                                    // Check if stealing from self
                                    for (int i = 0; i < static_cast<int>(possibleVictims.size()); ++i) {
                                        if (possibleVictims.at(i) == &curr_builder) {
                                            possibleVictims.erase(possibleVictims.begin() + i);
                                        }
                                    }

                                    // If there is someone to steal from, steal
                                    if (possibleVictims.size() > 0) {

                                        cout << "Builder " << curr_builder.getColour() << " can choose to steal from ";
                                        for (int i = 0; i < static_cast<int>(possibleVictims.size()); ++i) {
                                            cout << possibleVictims.at(i)->getColour();
                                            if ( i != static_cast<int>(possibleVictims.size()) - 1) {
                                                cout << ", ";
                                            }
                                        }

                                        cout << "." << endl << "Choose a builder to steal from." << endl;
                                        while (true) {
                                            string choice;
                                            bool goodChoice = false;
                                            if (read_one_valid<string>(&retTrue, choice)) {
                                                for (auto& victim : possibleVictims) {
                                                    if (victim->getColour() == choice) {
                                                        goodChoice = true;
                                                        Resource to_gain = victim->loseRandomResource();
                                                        if (to_gain != Resource::PARK) {
                                                            curr_builder.getHand().change(to_gain, 1);
                                                        }
                                                        cout << "Builder " << curr_builder.getColour() << " steals " << res_to_str(to_gain) << " from builder " << victim->getColour() << "." << endl;
                                                        break; 
                                                    }
                                                }
                                                if (goodChoice) {
                                                    break;
                                                }
                                            }
                                            cout << "Choose a valid builder to steal from." << endl;
                                        }
                                    } else {
                                        cout << "Builder " << curr_builder.getColour() << " has no builders to steal from." << endl;
                                    }
                                    break;
                                }
                            }
                        } else {
                            b->rolled(theRoll);
                            bool resGained = false;
                            for (int i = 0; i < static_cast<int>(builders.size()); ++i) {
                                if (builders.at(i).getHand() != prevResources.at(i)) {
                                    resGained = true;
                                    cout << "Builder " << builders[i].getColour() << " gained:" << endl;
                                    if (builders[i].getHand().get(Resource::BRICK) - prevResources[i].get(Resource::BRICK)) {
                                        cout << builders[i].getHand().get(Resource::BRICK) - prevResources[i].get(Resource::BRICK) << " brick" << endl;
                                    }
                                    if (builders[i].getHand().get(Resource::ENERGY) - prevResources[i].get(Resource::ENERGY)) {
                                        cout << builders[i].getHand().get(Resource::ENERGY) - prevResources[i].get(Resource::ENERGY) << " energy" << endl;
                                    }
                                    if (builders[i].getHand().get(Resource::GLASS) - prevResources[i].get(Resource::GLASS)) {
                                        cout << builders[i].getHand().get(Resource::GLASS) - prevResources[i].get(Resource::GLASS) << " glass" << endl;
                                    }
                                    if (builders[i].getHand().get(Resource::HEAT) - prevResources[i].get(Resource::HEAT)) {
                                        cout << builders[i].getHand().get(Resource::HEAT) - prevResources[i].get(Resource::HEAT) << " heat" << endl;
                                    }
                                    if (builders[i].getHand().get(Resource::WIFI) - prevResources[i].get(Resource::WIFI)) {
                                        cout << builders[i].getHand().get(Resource::WIFI) - prevResources[i].get(Resource::WIFI) << " WiFi" << endl;
                                    }
                                }
                            }
                            if (!resGained) {
                                cout << "No builders gained resources." << endl;
                            }
                        }

                        break;
                    }
                    cout << "Invalid command?\nTry 'load', 'fair', or 'roll'.\n";
                    
                }
                // ~Beginning of turn phase

                // During the turn phase
                while (true) {

                    string builderAction = read_valid<string>(&validTurnCmd, "Invalid command.\nTry 'help' for a list of valid commands.\n");

                    if (builderAction == "board") {
                        cout << b->getDesc() << endl;
                        continue;
                    } else if (builderAction == "status") {
                        cout << curr_builder.getStatusDesc() << endl;
                        continue;
                    } else if (builderAction == "residences") {
                        cout << curr_builder.getResidencesDesc();
                        continue;
                    } else if (builderAction == "build-road") {
                        int edgeNum ;
                        if (read_one_valid<int>(&validEdge, edgeNum)) {
                            if (curr_builder.buildRoad(&b->getEdge(edgeNum), false)) {
                                continue;
                            } else if (!(curr_builder.getHand() >= Road::getCost())) {
                                cout << "You do not have enough resources." << endl;
                            } else {
                                cout << "You cannot build here." << endl;
                            }
                        } else {
                            cout << "Invalid command." << endl;
                        }
                        continue;
                    } else if (builderAction == "build-res") {
                        int vertNum;
                        if (read_one_valid<int>(&validVertex, vertNum)) {
                            if (curr_builder.buildRes(&b->getVertex(vertNum), false)) {
                                continue;
                            } else if (!(curr_builder.getHand() >= Basement::getCost())) {
                                cout << "You do not have enough resources." << endl;
                            } else {
                                cout << "You cannot build here." << endl;
                            }
                        } else {
                            cout << "Invalid command." << endl;
                        }
                        continue;
                    } else if (builderAction == "improve") {
                        int vertNum;
                        if (read_one_valid<int>(&validVertex, vertNum)) {
                            if (!b->getVertex(vertNum).getBuilding()) {
                                cout << "You cannot build here." << endl;
                                continue;
                            }
                            try {
                                b->getVertex(vertNum).getBuilding()->getImproveResources();
                            } catch (...) {
                                cout << "Cannot improve a Tower." << endl;
                                continue;
                            }
                            if (curr_builder.improve(&b->getVertex(vertNum), false)) {
                                continue;
                            } else if (!(curr_builder.getHand() >= b->getVertex(vertNum).getBuilding()->getImproveResources())) {
                                // NOTE: GETIMPROVERESOURCES THROWS AN ERROR IF IMPROVING TO
                                cout << "You do not have enough resources." << endl;
                            } else {
                                cout << "You cannot build here." << endl;
                            }
                        } else {
                            cout << "Invalid command." << endl;
                        }
                        continue;
                    } else if (builderAction == "trade") {
                        string col;
                        if (read_one_valid<string>(&retTrue, col) && curr_builder.getColour() != col) {
                            for (auto& builder : builders) {
                                if (builder.getColour() == col) {
                                    string give;
                                    string take;
                                    if (read_one_valid<string>(&isValidResource, give) && read_one_valid<string>(&isValidResource, take)) {
                                        cout << curr_builder.getColour() << " offers " << builder.getColour() << " one " <<
                                            give << " for one " << take << "." << endl << "Does " << builder.getColour() <<
                                            " accept this offer?" << endl;
                                        string ans = read_valid<string>(&yes_no, "Please answer 'yes' or 'no'\n");
                                        if (ans == "yes") {
                                            Resource giveRes;
                                            Resource takeRes;
                                            if (give == "brick") giveRes = Resource::BRICK;
                                            else if (give == "energy") giveRes = Resource::ENERGY;
                                            else if (give == "glass") giveRes = Resource::GLASS;
                                            else if (give == "heat") giveRes = Resource::HEAT;
                                            else if (give == "wifi") giveRes = Resource::WIFI;
                                            else giveRes = Resource::PARK;
                                            if (take == "brick") takeRes = Resource::BRICK;
                                            else if (take == "energy") takeRes = Resource::ENERGY;
                                            else if (take == "glass") takeRes = Resource::GLASS;
                                            else if (take == "heat") takeRes = Resource::HEAT;
                                            else if (take == "wifi") takeRes = Resource::WIFI;
                                            else takeRes = Resource::PARK;
                                            if (!curr_builder.trade(giveRes, takeRes, &builder)) {
                                                cout << "You do not have enough resources." << endl;
                                            }
                                        } else {
                                            cout << "Trade not accepted." << endl;
                                        }
                                    } else {
                                        cout << "Invalid command." << endl;
                                    }
                                    break;
                                }
                            }
                        } else {
                            cout << "Invalid command.";
                        }
                        continue;
                    } else if (builderAction == "next") {
                        break;
                    } else if (builderAction == "save") {
                        string fname;
                        if (cin >> fname) {
                            ofstream file{fname};
                            if (gameBegun) {
                                turn = (turn + 1) % builders.size();
                            }
                            file << builders[turn].getColour() << endl;
            
                            for (auto& builder : builders) {

                            file << builder.saveOutput() << endl;

                            }

                            file << b->saveOutput() << endl;
                            file << goose->getIndex() << endl;
                        } else {
                            cout << "Invalid command." << endl;
                        }
                        continue;
                    } else if (builderAction == "help") {
                        cout << "Valid commands:" << endl << "board" << endl << "status" << endl <<
                        "residences" << endl << "build-road <edge#>" << endl << "build-res <housing#>" << 
                        endl << "improve <housing#>" << endl << "trade <colour> <give> <take>" << 
                        endl << "next" << endl << "save <file>" << endl << "help" << endl;
                        continue;
                    }

                    cout << "Invalid command.\nTry 'help' for a list of valid commands.\n";
                }
                // ~During the turn phase

                // Chcecking for winner
                bool isWinner = false;
                string winnerColour;
                for (auto &builder : builders) {

                    if (builder.getVictoryPoints() >= 10) {

                        isWinner = true;
                        winnerColour = builder.getColour();

                    }

                }

                if (isWinner) {

                    cout << "Builder " << winnerColour << " has gotten 10 victory points, they win! Congratulations!" << endl;
                    cout << "Would you like to play again?" << endl;
                    continueGame = read_valid<string>(&yes_no, "Invalid command?\nTry 'yes', or 'no'.\n");
                    break;

                }
                
                // Next turn
                turn = (turn + 1) % builders.size();
            }
            // ~Game loop

            if (continueGame == "no") {

                break;

            } else {

                goose->move(nullptr);
                loadBoard = false;
                fullSave = false;
                randomBoard = true;
                builders.clear();
                builders.reserve(4);
                turn = 0;
                startingBuildings = 0;

            }

        }

    } catch (...) {
        // save then terminate program due to EOF.
        ofstream file{"backup.sv"};

        if (gameBegun) {
            turn = (turn + 1) % builders.size();
        }

        file << builders[turn].getColour() << endl;
        
        for (auto& builder : builders) {

            file << builder.saveOutput() << endl;

        }

        file << b->saveOutput() << endl;
        file << goose->getIndex() << endl;
    }
}

