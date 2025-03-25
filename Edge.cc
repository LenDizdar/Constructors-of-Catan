#include "Edge.h"

using namespace std;

string Edge::getName() const {

    if (road) {

        return "A";

    }

    string s = to_string(index);
    return s;

}
