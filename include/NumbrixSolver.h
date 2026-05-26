#pragma once
#include <NumbrixBoard.h>

namespace numbrix {

class NumbrixSolver {
public:
    virtual bool solve(NumbrixBoard* board) = 0;
};

}