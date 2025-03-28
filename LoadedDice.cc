#include "LoadedDice.h"
#include <iostream>
#include <limits>

constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

int LoadedDice::genRoll() {
    int toRet;
    while (true) {
        std::cout << "Input a roll between 2 and 12:" << std::endl << ">";
        if (std::cin >> toRet) {
            if (2 <= toRet && toRet <= 12) {
                return toRet;
                break;
            }
        } else {
            if (std::cin.eof()) {
                break;
            }
            std::cin.clear();
            std::cin.ignore(max_size, '\n');
        }
        std::cout << "Invalid roll." << std::endl;
    }
    return -1;
}
