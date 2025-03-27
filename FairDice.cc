#include "FairDice.h"

FairDice::FairDice(unsigned seed) : Dice{}, rand{std::default_random_engine{seed}} {}

int FairDice::genRoll() {
    std::uniform_int_distribution<> distrib(1, 6);
    return distrib(rand) + distrib(rand);
}
