#include <HybridNumbrixSolver.h>
#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using numbrix::Coordinates;
using std::vector;
template <typename T>
using set = std::unordered_set<T>;

bool numbrix::HybridNumbrixSolver::hasValue(const int &value) const
{
    auto iter = valuesInBoard.find(value);
    return iter != valuesInBoard.end();
}

bool numbrix::HybridNumbrixSolver::checkPositive()
{
    return checkDirection(true);
}

bool numbrix::HybridNumbrixSolver::checkNegative()
{
    return checkDirection(false);
}

bool numbrix::HybridNumbrixSolver::checkDirection(bool pos)
{
    int nextValue;
    int twoAfter;
    std::unordered_set<int> *thisList;
    std::unordered_set<int> *otherList;
    if (pos) {
        thisList = &positive;
        otherList = &negative;
    }
    else {
        thisList = &negative;
        otherList = &positive;
    }
    bool changed = false;
    auto it = thisList->begin();
    while (it != thisList->end()) {
        int value = *it;
        Coordinates c = locations.at(value);
        Coordinates next(c);
        nextValue = pos ? value+1 : value-1;
        twoAfter = pos ? value+2 : value-2;
        if (hasValue(nextValue)) {
            if (thisList->find(nextValue) == thisList->end()) thisList->insert(nextValue);
            it = thisList->erase(it);
            continue;
        }
        else if (hasValue(twoAfter)) {
            Coordinates tAL = locations.at(twoAfter);

            Coordinates nextL = c;
            bool foundSpot = false;

            if (abs(c.x-tAL.x) == 2 ) {
                nextL.x = (c.x+tAL.x)/2;
                foundSpot = true;
            }
            else if (abs(c.y-tAL.y) == 2) {
                nextL.y = (c.y+tAL.y)/2;
                foundSpot = true;
            }
            else {
                bool one = empty({c.x, tAL.y});
                bool other = empty({tAL.x, c.y});

                if (one ^ other) { // xor
                    if (one) {
                        nextL.y = tAL.y;
                    }
                    else {
                        nextL.x = tAL.x;
                    }
                    foundSpot = true;
                }
                else {

                    // check if either are valid paths for one of the other neighbors to take. If one has no other valid path going through it, 

                    int valueOppositeInitial;
                    int valueOppositeTwoAhead;
                    // get the column number of the cell on the same row as this value
                    int sameRowCol;
                    if (c.y < tAL.y) {
                        sameRowCol = c.y+2;
                    }
                    else {
                        sameRowCol = c.y-2;
                    }
                    // get the row number of the cell on the same column as twoAfter
                    int sameColRow;
                    if (tAL.x > c.x) {
                        sameColRow = tAL.x-2;
                    }
                    else {
                        sameColRow = tAL.x+2;
                    }
                    if (sameRowCol < 0 || sameRowCol >= numCols) {
                        valueOppositeInitial = -1;
                    }
                    else {
                        valueOppositeInitial = board->getValue(c.x, sameRowCol);
                    }
                    if (sameColRow < 0 || sameColRow >= numRows) {
                        valueOppositeTwoAhead = -1;
                    }
                    else {
                        valueOppositeTwoAhead = board->getValue(sameColRow, tAL.y);
                    }
                    if (!hasOtherPossiblePath(value, twoAfter, valueOppositeInitial, valueOppositeTwoAhead)) {
                        foundSpot = true;
                        nextL.x = (sameColRow + tAL.x)/2;
                        nextL.y = (sameRowCol + c.y)/2;
                    }
                    else {
                        // now we do the same checks for the other side
                        if (c.x < tAL.x) {
                            sameColRow = c.x+2;
                        }
                        else {
                            sameColRow = c.x-2;
                        }
                        if (tAL.y > c.y) {
                            sameRowCol = tAL.y-2;
                        }
                        else {
                            sameRowCol = tAL.y+2;
                        }

                        if (sameRowCol < 0 || sameRowCol >= numCols) {
                            valueOppositeTwoAhead = -1;
                        }
                        else {
                            valueOppositeTwoAhead = board->getValue(tAL.x, sameRowCol);
                        }

                        if (sameColRow < 0 || sameColRow >= numRows) {
                            valueOppositeInitial = -1;
                        }
                        else {
                            valueOppositeInitial = board->getValue(sameColRow, c.y);
                        }
                        if (!hasOtherPossiblePath(value, twoAfter, valueOppositeInitial, valueOppositeTwoAhead)) {
                            foundSpot = true;
                            nextL.x = (sameColRow + c.x)/2;
                            nextL.y = (sameRowCol + tAL.y)/2;
                        }
                    }
                }
            }

            if (foundSpot) {
                insertValue(nextL, nextValue);
                otherList->erase(otherList->find(twoAfter));
                it = thisList->erase(it);
                changed = true;
                // std::cout << "Current Board:" << std::endl << board->toString() << std::endl << std::endl;
                continue;
            }

        }
        else {
            int count = 0;
            bool up = false, down = false, left = false, right = false;
            if (empty(c.getCoordinatesUp())){ 
                count++;
                up = true;
            }
            if (empty(c.getCoordinatesDown())) {
                count++;
                down = true;
            }
            if (empty(c.getCoordinatesLeft())) {
                count++;
                left = true;
            }
            if (empty(c.getCoordinatesRight())) {
                count++;
                right = true;
            }
            if (count > 1 && up && !isValidPath(c.getCoordinatesUp(), nextValue, DOWN)) {
                count--;
                up = false;
            }
            if (count > 1 && down && !isValidPath(c.getCoordinatesDown(), nextValue, UP)) {
                count--;
                down = false;
            }
            if (count > 1 && left && !isValidPath(c.getCoordinatesLeft(), nextValue, RIGHT)) {
                count--;
                left = false;
            }
            if (count > 1 && right && !isValidPath(c.getCoordinatesRight(), nextValue, LEFT)) {
                count--;
                right = false;
            }
            if (count == 1) {
                Coordinates next;

                if (up) next = c.getCoordinatesUp();
                else if (down) next = c.getCoordinatesDown();
                else if (left) next = c.getCoordinatesLeft();
                else next = c.getCoordinatesRight();

                insertValue(next, nextValue);
                thisList->insert(nextValue);
                it = thisList->erase(it);
                changed = true;
                // std::cout << "Current Board:" << std::endl << board->toString() << std::endl << std::endl;
                continue;
            }
        }
        ++it;
    }
    return changed;
}

bool numbrix::HybridNumbrixSolver::hasOtherPossiblePath(const int &thisValue, const int& twoAfter, const int &valueOppositeInitial, const int &valueOppositeTwoAhead)
{
    if (valueOppositeInitial == 0 || valueOppositeTwoAhead == 0){ // If either cell is open, all bets are off
        return true; 
    }
    // Check all possible routes through this cell. If one of the other routes are valid, the route between thisValue and twoAhead is not guaranteed to pass through this cell and we return false
    if (valueOppositeInitial != -1) { // if valueOppositeInitial is a wall, we can skip all these checks as you can't route into a wall
        if (valueOppositeTwoAhead != -1 && abs(valueOppositeInitial - valueOppositeTwoAhead) == 2 && !hasValue((valueOppositeInitial + valueOppositeTwoAhead)/2)) { // if these two values are two apart and the value between them is not on the board, it is possible they route through this cell
            return true;
        }
        else if (abs(valueOppositeInitial - thisValue) == 2 && !hasValue((valueOppositeInitial + thisValue)/2)) {
            return true;
        }
        else if (abs(valueOppositeInitial - twoAfter) == 2 && !hasValue((valueOppositeInitial + twoAfter)/2)) {
            return true;
        }
    }
    else if (valueOppositeTwoAhead == maxValue-1 || valueOppositeTwoAhead == 2) { // if valueOppositeInitial is a wall and the other value is maxValue-1 or 2, maxValue or 1 could path into this cell.
        return true;
    }

    if (valueOppositeTwoAhead != -1) { // if valueOppositeTwoAhead is a wall, we can skip all these checks as you can't route into a wall
        if (abs(valueOppositeTwoAhead - thisValue) == 2 && !hasValue((valueOppositeTwoAhead + thisValue)/2)) {
            return true;
        }
        else if (abs(valueOppositeTwoAhead - twoAfter) == 2 && !hasValue((valueOppositeTwoAhead + twoAfter)/2)) {
            return true;
        }
    }
    else if (valueOppositeInitial == maxValue-1 || valueOppositeInitial == 2) { // if valueOppositeTwoAhead is a wall and the other value is maxValue-1 or 2, maxValue or 1 could path into this cell.
        return true;
    }
    return false;
}

// bool numbrix::HybridNumbrixSolver::isCellOccupied(const Coordinates &coordinates)
// {
//     return occupiedCells.find(coordinates) != occupiedCells.end();
// }

bool numbrix::HybridNumbrixSolver::isValidPath(const Coordinates& c, const int &value, const Direction &from)
{
    // If we didn't come from the top, check if the path can go through the cell above
    if (from != UP) {
        Coordinates up = c.getCoordinatesUp();
        int upVal = (up.x < 0) ? -1 : board->getValue(up.x, up.y);
        if (upVal == 0 || abs(value - upVal) == 1) {
            return true;
        }
    }
    // If we didn't come from the right, check if the path can go through the cell to the right
    if (from != RIGHT) {
        Coordinates right = c.getCoordinatesRight();
        int rightVal = (right.y >= numCols) ? -1 : board->getValue(right.x, right.y);
        if (rightVal == 0 || abs(value-rightVal) == 1) {
            return true;
        }
    }
    // If we didn't come from the bottom, check if the path can go through the cell below
    if (from != DOWN) {
        Coordinates down = c.getCoordinatesDown();
        int downVal = (down.x >= numRows) ? -1 : board->getValue(down.x, down.y);
        if (downVal == 0 || abs(value-downVal) == 1) {
            return true;
        }
    }
    // if we didn't come from the left, check if the path can go through the cell to the left
    if (from != LEFT) {
        Coordinates left = c.getCoordinatesLeft();
        int leftVal = (left.y < 0) ? -1 : board->getValue(left.x, left.y);
        if (leftVal == 0 || abs(value-leftVal) == 1) {
            return true;
        }
    }

    return false;
}

void numbrix::HybridNumbrixSolver::insertValue(const Coordinates& c, const int &value)
{
    board->setValue(c.x, c.y, value);
    locations.insert({value, c});
    // occupiedCells.insert(location);
    valuesInBoard.insert(value);
}

bool numbrix::HybridNumbrixSolver::empty(const Coordinates& c)
{
    if (c.x < 0 || c.x >= numRows || c.y < 0 || c.y >= numCols) {
        return false;
    }
    return board->getValue(c.x, c.y) == 0;
}

bool numbrix::HybridNumbrixSolver::hasSufficientEmptySpace()
{
    std::unordered_set<Coordinates> posInPath;
    int startValue;
    bool accending = true;
    if (hasValue(maxValue)) {
        startValue = maxValue;
        for (auto num : negative) {
            if (num < startValue) startValue = num;
        }
        accending = false;
    }
    else {
        startValue = 1;
        for (auto num : positive) {
            if (num > startValue) startValue = num;
        }
    }
    Coordinates start = locations[startValue];
    return recursiveEmptySpaceFinder(start, startValue, posInPath, accending);
}

bool numbrix::HybridNumbrixSolver::recursiveEmptySpaceFinder(const Coordinates &currentPos, const int &currentValue, std::unordered_set<Coordinates> &currentPath, bool accending)
{
    int valInCell = board->getValue(currentPos.x, currentPos.y);
    if (valInCell != 0 && valInCell != currentValue) return false;
    currentPath.insert(currentPos);
    if (accending && currentValue == maxValue)  {
        int startValue = maxValue;
        for (auto num : negative) {
            if (num < startValue) startValue = num;
        }
        Coordinates start = locations[startValue];
        return recursiveEmptySpaceFinder(start, startValue, currentPath, false);
    }
    if (!accending && currentValue == 1) return true;
    
    int nextValue = (accending) ? currentValue+1:currentValue-1;
    Coordinates next (currentPos);
    next.x--;
    if (next.x >= 0 && currentPath.find(next) == currentPath.end() && recursiveEmptySpaceFinder(next, nextValue, currentPath, accending)) {
        return true;
    }
    next.x += 2;
    if (next.x < numRows && currentPath.find(next) == currentPath.end() && recursiveEmptySpaceFinder(next, nextValue, currentPath, accending)) {
        return true;
    }
    next.x--;
    next.y--;
    if (next.y >= 0 && currentPath.find(next) == currentPath.end() && recursiveEmptySpaceFinder(next, nextValue, currentPath, accending)) {
        return true;
    }
    next.y += 2;
    if (next.y < numCols && currentPath.find(next) == currentPath.end() && recursiveEmptySpaceFinder(next, nextValue, currentPath, accending)) {
        return true;
    }

    currentPath.erase(currentPos);
    return false;
}

bool numbrix::HybridNumbrixSolver::hasEmptyNeighbor(const Coordinates& c)
{
    return (empty(c.getCoordinatesUp()) || empty(c.getCoordinatesDown()) || empty(c.getCoordinatesLeft()) || empty(c.getCoordinatesRight())); // compiler should optimize this so it returns true at the first empty cell
}

int numbrix::HybridNumbrixSolver::rankDirection(const Coordinates &currentLocation, const Direction &d, const int& valueToPut, const Direction &from, const int& target, const Coordinates& targetCoordinates)
{
    // if you're trying to go the same direction you came from, don't
    if (d == from) return ImpassableScore;
    // if you're trying to go out of bounds, don't
    if ((currentLocation.x == 0 && d == UP) || (currentLocation.x == numRows-1 && d == DOWN) 
    || (currentLocation.y == 0 && d == LEFT) || (currentLocation.y == numCols-1 && d == RIGHT)) return ImpassableScore;
    // if you're trying to enter an occupied cell, don't
    Coordinates next = currentLocation.getCoordinatesInDirection(d);
    if (Coordinates::getDistanceBetweenCoordinates(next, targetCoordinates) > target-valueToPut) return ImpassableScore;
    int nextValue = board->getValue(next.x, next.y);
    if (valueToPut == target && nextValue == target) return CompletedPathNeighborScore;
    if (nextValue != 0) return ImpassableScore;
    int score = 0;
    if (d != DOWN)  score += scoreCell(currentLocation.getCoordinatesInDirection(UP), valueToPut);
    if (d != UP)    score += scoreCell(currentLocation.getCoordinatesInDirection(DOWN), valueToPut);
    if (d != RIGHT) score += scoreCell(currentLocation.getCoordinatesInDirection(LEFT), valueToPut);
    if (d != LEFT)  score += scoreCell(currentLocation.getCoordinatesInDirection(RIGHT), valueToPut);
    return score;
}

int numbrix::HybridNumbrixSolver::scoreCell(const Coordinates &currentLocation, const int &valueInNeighbor)
{
    if (currentLocation.x < 0 || currentLocation.x >= numRows || currentLocation.y < 0 || currentLocation.y >= numCols) return WallNeighborScore;
    int value = board->getValue(currentLocation.x, currentLocation.y);
    if (value == 0) return EmptyNeighborScore;
    if (value == valueInNeighbor+1) return CompletesPathScore;
    if (positive.find(value) != positive.end() || negative.find(value) != negative.end()) {
        return UnfinishedRouteScore;
    }
    else {
        return CompletedPathNeighborScore;
    }
}

bool numbrix::HybridNumbrixSolver::solveSegment(const Coordinates& currentLocation,const int &currentValue, const Segment &currentSegment, const Coordinates& targetCoordinates, const Direction &from)
{
    if (currentValue == currentSegment.endVal) {
        // check if the current path is valid
        if (!hasSufficientEmptySpace()) return false;
        // load up the next segment and send
        if (segmentStack.empty()) {
            return true;
        }
        else {
            auto nextSegment = segmentStack.top();
            segmentStack.pop();
            Coordinates start = locations[nextSegment.startVal];
            Coordinates nextTargetCoords = locations[nextSegment.endVal];
            if (!solveSegment(start, nextSegment.startVal, nextSegment, nextTargetCoords, NONE)) {
                // Put the following segment back on the stack and try again
                segmentStack.push(nextSegment);
                return false;
            }
            else {
                return true;
            }
        }
    }
    board->setValue(currentLocation.x, currentLocation.y, currentValue);
    int priorities[] = {0,0,0,0};
    Direction directionsToTest[] = {UP, RIGHT, DOWN, LEFT};
    for (int k = 0; k < 4; k++) {
        priorities[k] = rankDirection(currentLocation, directionsToTest[k], currentValue+1, from, currentSegment.endVal, targetCoordinates);
    }
    std::sort(directionsToTest, directionsToTest+4, [=](const Direction& a, const Direction& b) {
        return priorities[a] > priorities[b];
    });
    // cout << "Directions and their priorities:" << endl;
    for (int k = 0; k < 4; k++) {
        Direction nextDirection = directionsToTest[k];
        // cout << toString(nextDirection) << ": " << priorities[nextDirection] << endl;
        // If the potential next direction is out of bounds or otherwise not a valid direction, don't go there. Since it is sorted in decending priority, as soon as we hit one we're done
        if (priorities[nextDirection] == ImpassableScore) break;
        Coordinates next = currentLocation.getCoordinatesInDirection(directionsToTest[k]);
        if (solveSegment(next, currentValue+1, currentSegment, targetCoordinates, reverseDirection(nextDirection))) {
            return true;
        }
    }
    board->setValue(currentLocation.x, currentLocation.y, 0);
    return false;
}

int numbrix::HybridNumbrixSolver::rankSegment(const Segment &seg)
{
    Coordinates startC = locations[seg.startVal];
    Coordinates endC = locations[seg.endVal];
    int distance = Coordinates::getDistanceBetweenCoordinates(startC, endC);
    int numSep = seg.endVal-seg.startVal;
    return numSep - distance;
}

bool numbrix::HybridNumbrixSolver::solve(NumbrixBoard *board)
{
    this->board = board;
    numRows = board->getNumRows();
    numCols = board->getNumCols();
    int minValue = numRows * numCols;
    maxValue = minValue;
    int x = 0;
    int y = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            int value = board->getValue(i, j);
            if (value != 0) {
                if (value < minValue) {
                    minValue = value;
                    x = i;
                    y = j;
                }
                if (value != 1) negative.insert(value);
                if (value != maxValue) positive.insert(value);
                valuesInBoard.insert(value);
                locations.insert({value, {i, j}});
            }
        }
    }

    bool changed = true;

    while (changed) {
        changed = false;
        changed |= checkPositive();
        changed |= checkNegative();
    }

    std::cout << "Was able to get this with jiggery-pokery: " << std::endl << board->toString() << std::endl << std::endl;

    std::vector<Segment> segments;
    for (auto item : positive) {
        int i;
        for (i = item+1; i < maxValue+1; i++) {
            if (hasValue(i)) {
                break;
            }
        }
        if (i != maxValue+1) segments.push_back({item, i});
    }
    std::sort(segments.begin(), segments.end(), [=](const Segment &a, const Segment &b) {
        return rankSegment(a) > rankSegment(b);
    });
    // add segments to queue
    vector<vector<vector<Coordinates>>> possiblePaths;
    // cout << "Segments to be added" << endl;
    for (auto segment:segments) {
        // cout << std::get<0>(segment) << " " << std::get<1>(segment) << endl;
        segmentStack.push(segment);
    }
    auto startSegment = segmentStack.top();
    segmentStack.pop();
    Coordinates startC = locations[startSegment.startVal];
    Coordinates endC = locations[startSegment.endVal];
    bool result = solveSegment(startC, startSegment.startVal, startSegment, endC, NONE);
    maxValue = 0;
    valuesInBoard.clear();
    positive.clear();
    negative.clear();
    locations.clear();
    while (!segmentStack.empty()) segmentStack.pop();
    return result;
}
