#ifndef RANDOMBOARD_H
#define RANDOMBOARD_H
#include "Board.h"

class RandomBoard : public Board {

    unsigned seed; // Seed for random number generator
    
    public:
        RandomBoard(unsigned seed); // Constructor

};

#endif
