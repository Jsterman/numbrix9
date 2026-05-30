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
    void insertValue(const int &i, const int &j, const int &value);
    bool empty(int i, int j);
public:
    virtual bool solve(NumbrixBoard *board);
};

}