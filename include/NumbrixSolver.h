#pragma once
#include <NumbrixBoard.h>

class NumbrixSolver {
public:
    virtual bool solve(NumbrixBoard*) = 0;
};