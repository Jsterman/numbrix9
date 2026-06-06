#pragma once
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <RecursiveNumbrixSolver.h>

namespace numbrix {

class HybridNumbrixSolver : public NumbrixSolver {
protected:
    int numRows;
    int numCols;
    int maxValue;
    NumbrixBoard *board;
    std::unordered_set<int> valuesInBoard;
    std::unordered_map<int, std::tuple<int, int>> locations;
    std::unordered_set<int> positive;
    std::unordered_set<int> negative;
    std::stack<std::tuple<int, int>> segmentQueue;
    bool hasValue(const int &value) const;
    bool checkPositive();
    bool checkNegative();
    bool checkDirection(bool pos);
    bool hasOtherPossiblePath(const int &thisValue, const int& twoAfter, const int &valueAcrossFromInitial, const int &valueAcrossFromTwoAhead);
    bool isValidPath(const int &row, const int &column, const int &value, const Direction &from);
    void insertValue(const int &i, const int &j, const int &value);
    bool empty(const int &i, const int &j);
    bool hasEmptyNeighbor(const int &i, const int &j);
    bool solveSegment(const int &i, const int &j, const int &start, const int &current, const int& target, const Direction &from);
    int rankSegment(const int &start, const int &end);
public:
    virtual bool solve(NumbrixBoard *board);
};

}