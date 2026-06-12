#pragma once
#include <limits>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <RecursiveNumbrixSolver.h>
#include <Coordinates.h>
#include <Segment.h>

namespace numbrix {

class HybridNumbrixSolver : public NumbrixSolver {
protected:
    static const int CompletesPathScore = 1'000'000;
    static const int WallNeighborScore = 2;
    static const int CompletedPathNeighborScore = 4;
    static const int EmptyNeighborScore = -1;
    static const int UnfinishedRouteScore = -2;
    static const int ImpassableScore = std::numeric_limits<int>::min();
    int numRows;
    int numCols;
    int maxValue;
    NumbrixBoard *board;
    std::unordered_set<int> valuesInBoard;
    std::unordered_map<int, Coordinates> locations;
    std::unordered_set<Coordinates> occupiedCells;
    std::unordered_set<int> positive;
    std::unordered_set<int> negative;
    std::stack<Segment> segmentStack;
    bool hasValue(const int &value) const;
    bool checkPositive();
    bool checkNegative();
    bool checkDirection(bool pos);
    bool hasOtherPossiblePath(const int &thisValue, const int& twoAfter, const int &valueAcrossFromInitial, const int &valueAcrossFromTwoAhead);
    // bool isCellOccupied(const Coordinates& coordinates);
    bool isValidPath(const Coordinates& c, const int &value, const Direction &from);
    void insertValue(const Coordinates &c, const int &value);
    bool empty(const Coordinates& c);
    bool hasSufficientEmptySpace(bool write=false);
    bool recursiveEmptySpaceFinder(const Coordinates& currentPos, const int& currentValue, std::unordered_set<Coordinates>& currentPath, bool accending, bool write=false);
    bool hasEmptyNeighbor(const Coordinates& c);
    int rankDirection(const Coordinates& currentLocation, const Direction& d, const int& valueToPut, const Direction& from, const int& target, const Coordinates& targetCoordinates);
    int scoreCell(const Coordinates& currentLocation, const int& valueInNeighbor);
    bool solveSegment(const Coordinates& currentLocation, const int &currentValue, const Segment& currentSegment, const Coordinates& targetCoordinates, const Direction &from);
    int rankSegment(const Segment& seg);
public:
    virtual bool solve(NumbrixBoard *board);
};

}