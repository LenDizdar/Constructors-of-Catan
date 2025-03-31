#ifndef CONSTRUCTABLE_H
#define CONSTRUCTABLE_H

#include <string>

class Constructable {
    std::string builderColour;
    public:
        // any Constructable must have a valid builderColour
        explicit Constructable(std::string colour) : builderColour{colour} {}
        
        std::string getColour() const { return builderColour; }

        virtual ~Constructable() = 0;
};

#endif
