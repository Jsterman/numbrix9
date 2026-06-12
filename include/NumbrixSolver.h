#pragma once
#include <NumbrixBoard.h>

namespace numbrix {

std::string toString(Direction d);
Direction reverseDirection(Direction d);

class NumbrixSolver {
public:
    virtual bool solve(NumbrixBoard* board) = 0;
};

}