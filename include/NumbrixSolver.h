#pragma once
#include <NumbrixBoard.h>

namespace numbrix {

enum Direction {
    NONE=-1,
    UP,
    RIGHT,
    DOWN,
    LEFT
};

std::string toString(Direction d);
Direction reverseDirection(Direction d);

class NumbrixSolver {
public:
    virtual bool solve(NumbrixBoard* board) = 0;
};

}