#include "FairDice.h"

#include <random>

int FairDice::genRoll() {
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 6);
    // above from cppreference for uniform_int_distribution example

    return distrib(gen) + distrib(gen);
}
