#ifndef LOADEDBOARD_H
#define LOADEDBOARD_H
#include <string>
#include "Board.h"

class LoadedBoard : public Board {
    
    public:
        LoadedBoard(std::string fileName, bool saveFile); // Constructor

};

#endif
