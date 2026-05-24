#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <NumbrixBoard.h>

namespace numbrix {

class NumbrixSolver {
private:
    int numberOfReads = 0;
    int numberOfWrites = 0;
    int numRows;
    int numCols;
    int maxValue;
    NumbrixBoard originalBoard;
    NumbrixBoard board;
    std::unordered_set<int> valuesInBoard;
    std::unordered_map<int, std::tuple<int, int>> valueLocations;
    int getValue(const int &row, const int &column);
    void setValue(const int &row, const int &column, const int &value);
    bool hasValue(const int &value) const;
    bool decendingRecSolver(const int &row, const int &column, const int &value);
    bool accendingRecSolver(const int &row, const int &column, const int &value);
public:
    NumbrixSolver(NumbrixBoard* board);
    bool solveRecursively();
    int getNumberOfReads();
    int getNumberOfWrites();
    void resetBoard();
    std::string getBoard();
};

}