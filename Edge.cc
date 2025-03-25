#include "Edge.h"
#include "Road.h"

using namespace std;

Edge::~Edge() = default;

string Edge::getName() const {

    if (road) {

        return "A";

    }

    string s = to_string(index);
    return s;

}
