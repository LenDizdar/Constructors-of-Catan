#ifndef RANDOMBOARD_H
#define RANDOMBOARD_H
#include "Board.h"
#include <random>

class RandomBoard : public Board {

    unsigned seed; // Seed for random number generator
    
    public:
        RandomBoard(std::default_random_engine rand); // Constructor

};

#endif
