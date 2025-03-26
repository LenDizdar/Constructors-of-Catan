#ifndef DICE_H
#define DICE_H

class Dice {
    virtual int genRoll() = 0;
    public:
        ~Dice() = default;
        int roll();
};

#endif
