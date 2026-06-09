#pragma once
#include <limits>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <RecursiveNumbrixSolver.h>

namespace numbrix {

struct Coordinates {
    int x;
    int y;
    Coordinates(int x, int y) : x(x), y(y) {}
    bool operator==(const Coordinates &b) const {
        return x == b.x && y == b.y;
    }
    bool operator!=(const Coordinates &b) const {
        return x != b.x || y != b.y;
    }
    friend std::ostream& operator<<(std::ostream& os, const Coordinates& c) {
        return os << "(" << c.x << "," << c.y << ")";
    }
    static int getDistanceBetweenCoordinates(const Coordinates &one, const Coordinates &other) {
        return abs(one.x - other.x) + abs(one.y - other.y);
    }
};

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
    std::unordered_map<int, std::tuple<int, int>> locations;
    std::unordered_set<int> positive;
    std::unordered_set<int> negative;
    std::stack<std::tuple<int, int>> segmentStack;
    bool hasValue(const int &value) const;
    bool checkPositive();
    bool checkNegative();
    bool checkDirection(bool pos);
    bool hasOtherPossiblePath(const int &thisValue, const int& twoAfter, const int &valueAcrossFromInitial, const int &valueAcrossFromTwoAhead);
    bool isValidPath(const int &row, const int &column, const int &value, const Direction &from);
    void insertValue(const int &i, const int &j, const int &value);
    bool empty(const int &i, const int &j);
    bool hasSufficientEmptySpace();
    bool recursiveEmptySpaceFinder(const Coordinates& currentPos, const int& currentValue, std::unordered_set<Coordinates>& currentPath, bool accending);
    bool hasEmptyNeighbor(const int &i, const int &j);
    Coordinates getCoordinates(const int& i, const int& j, const Direction& d);
    int rankDirection(const int& i, const int& j, const Direction& d, const int& valueToPut, const Direction& from, const int& target, const Coordinates& targetCoordinates);
    int scoreCell(const int& i, const int& j, const int& valueInNeighbor);
    bool solveSegment(const int &i, const int &j, const int &start, const int &current, const int& target, const Coordinates& targetCoordinates, const Direction &from);
    int rankSegment(const int &start, const int &end);
public:
    virtual bool solve(NumbrixBoard *board);
};

}
// This part is so that we can use Coordinates in structures that require hashing (e.g. unsorted_set and unordered_map)
namespace std {
    template<>
    struct hash<numbrix::Coordinates> {
        std::size_t operator()(const numbrix::Coordinates& c) const noexcept {
            std::size_t h1 = std::hash<int>{}(c.x);
            std::size_t h2 = std::hash<int>{}(c.y);
            return h1^(h2<<1);
        }
    };
}