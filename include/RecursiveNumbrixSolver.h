#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <NumbrixSolver.h>

namespace numbrix {

class RecursiveNumbrixSolver: public NumbrixSolver {
protected:
    int numRows;
    int numCols;
    int maxValue;
    NumbrixBoard *board;
    std::unordered_set<int> valuesInBoard;
    bool hasValue(const int &value) const;
    bool decendingRecSolver(const int &row, const int &column, const int &value, const Direction &from);
    bool accendingRecSolver(const int &row, const int &column, const int &value, const Direction &from);
public:
    RecursiveNumbrixSolver();
    virtual bool solve(NumbrixBoard* board);
};

}