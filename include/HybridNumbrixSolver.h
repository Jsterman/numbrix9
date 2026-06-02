#pragma once
#include <unordered_map>
#include <RecursiveNumbrixSolver.h>

namespace numbrix {

class HybridNumbrixSolver : public RecursiveNumbrixSolver {
protected:
    std::unordered_map<int, std::tuple<int, int>> locations;
    std::unordered_set<int> positive;
    std::unordered_set<int> negative;
    bool checkPositive();
    bool checkNegative();
    bool checkDirection(bool pos);
    bool hasOtherPossiblePath(const int &thisValue, const int& twoAfter, const int &valueAcrossFromInitial, const int &valueAcrossFromTwoAhead);
    bool isValidPath(const int &thisValue, const int &nextValue, const int &twoAfter, const int &valueAcrossFromInitial, const int &valueAcrossFromTwoAhead);
    void insertValue(const int &i, const int &j, const int &value);
    bool empty(const int &i, const int &j);
    bool hasEmptyNeighbor(const int &i, const int &j);
public:
    virtual bool solve(NumbrixBoard *board);
};

}