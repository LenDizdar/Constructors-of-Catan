#ifndef FAIR_DICE_H
#define FAIR_DICE_H
#include <random>
#include "Dice.h"

class FairDice : public Dice {
    std::default_random_engine rand;
    int genRoll();
    public:
        FairDice(unsigned seed);
};

#endif
