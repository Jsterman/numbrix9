#include <HybridNumbrixSolver.h>
#include <algorithm>
#include <iostream>
#include <vector>

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
        const auto [i, j] = locations.at(value);
        nextValue = pos ? value+1 : value-1;
        twoAfter = pos ? value+2 : value-2;
        if (hasValue(nextValue)) {
            if (thisList->find(nextValue) == thisList->end()) thisList->insert(nextValue);
            it = thisList->erase(it);
            continue;
        }
        else if (hasValue(twoAfter)) {
            const auto [oi, oj] = locations.at(twoAfter);

            int nexti = i, nextj = j;
            bool foundSpot = false;

            if (abs(i-oi) == 2 ) {
                nexti = (i+oi)/2;
                foundSpot = true;
            }
            else if (abs(j-oj) == 2) {
                nextj = (j+oj)/2;
                foundSpot = true;
            }
            else {
                bool one = empty(i, oj);
                bool other = empty(oi, j);

                if (one ^ other) { // xor
                    if (one) {
                        nextj = oj;
                    }
                    else {
                        nexti = oi;
                    }
                    foundSpot = true;
                }
                else {

                    // check if either are valid paths for one of the other neighbors to take. If one has no other valid path going through it, 

                    int valueOppositeInitial;
                    int valueOppositeTwoAhead;
                    // get the column number of the cell on the same row as this value
                    int sameRowCol;
                    if (j < oj) {
                        sameRowCol = j+2;
                    }
                    else {
                        sameRowCol = j-2;
                    }
                    // get the row number of the cell on the same column as twoAfter
                    int sameColRow;
                    if (oi > i) {
                        sameColRow = oi-2;
                    }
                    else {
                        sameColRow = oi+2;
                    }
                    if (sameRowCol < 0 || sameRowCol >= numCols) {
                        valueOppositeInitial = -1;
                    }
                    else {
                        valueOppositeInitial = board->getValue(i, sameRowCol);
                    }
                    if (sameColRow < 0 || sameColRow >= numRows) {
                        valueOppositeTwoAhead = -1;
                    }
                    else {
                        valueOppositeTwoAhead = board->getValue(sameColRow, oj);
                    }
                    if (!hasOtherPossiblePath(value, twoAfter, valueOppositeInitial, valueOppositeTwoAhead)) {
                        foundSpot = true;
                        nexti = (sameColRow + oi)/2;
                        nextj = (sameRowCol + j)/2;
                    }
                    else {
                        // now we do the same checks for the other side
                        if (i < oi) {
                            sameColRow = i+2;
                        }
                        else {
                            sameColRow = i-2;
                        }
                        if (oj > j) {
                            sameRowCol = oj-2;
                        }
                        else {
                            sameRowCol = oj+2;
                        }

                        if (sameRowCol < 0 || sameRowCol >= numCols) {
                            valueOppositeTwoAhead = -1;
                        }
                        else {
                            valueOppositeTwoAhead = board->getValue(oi, sameRowCol);
                        }

                        if (sameColRow < 0 || sameColRow >= numRows) {
                            valueOppositeInitial = -1;
                        }
                        else {
                            valueOppositeInitial = board->getValue(sameColRow, j);
                        }
                        if (!hasOtherPossiblePath(value, twoAfter, valueOppositeInitial, valueOppositeTwoAhead)) {
                            foundSpot = true;
                            nexti = (sameColRow + i)/2;
                            nextj = (sameRowCol + oj)/2;
                        }
                    }
                }
            }

            if (foundSpot) {
                insertValue(nexti, nextj, nextValue);
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
            if (empty(i-1, j)){ 
                count++;
                up = true;
            }
            if (empty(i+1, j)) {
                count++;
                down = true;
            }
            if (empty(i, j-1)) {
                count++;
                left = true;
            }
            if (empty(i, j+1)) {
                count++;
                right = true;
            }
            if (count > 1 && up && !isValidPath(i-1, j, nextValue, DOWN)) {
                count--;
                up = false;
            }
            if (count > 1 && down && !isValidPath(i+1, j, nextValue, UP)) {
                count--;
                down = false;
            }
            if (count > 1 && left && !isValidPath(i, j-1, nextValue, RIGHT)) {
                count--;
                left = false;
            }
            if (count > 1 && right && !isValidPath(i, j+1, nextValue, LEFT)) {
                count--;
                right = false;
            }
            if (count == 1) {
                int nexti = i;
                int nextj = j;

                if (up) nexti = i-1;
                else if (down) nexti = i+1;
                else if (left) nextj = j-1;
                else nextj = j+1;

                insertValue(nexti, nextj, nextValue);
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

bool numbrix::HybridNumbrixSolver::isValidPath(const int &i, const int &j, const int &value, const Direction &from)
{
    // If we didn't come from the top, check if the path can go through the cell above
    if (from != UP) {
        int upVal = (i-1 < 0) ? -1 : board->getValue(i-1, j);
        if (upVal == 0 || abs(value - upVal) == 1) {
            return true;
        }
    }
    // If we didn't come from the right, check if the path can go through the cell to the right
    if (from != RIGHT) {
        int rightVal = (j+1 >= numCols) ? -1 : board->getValue(i, j+1);
        if (rightVal == 0 || abs(value-rightVal) == 1) {
            return true;
        }
    }
    // If we didn't come from the bottom, check if the path can go through the cell below
    if (from != DOWN) {
        int downVal = (i+1 >= numRows) ? -1 : board->getValue(i+1, j);
        if (downVal == 0 || abs(value-downVal) == 1) {
            return true;
        }
    }
    // if we didn't come from the left, check if the path can go through the cell to the left
    if (from != LEFT) {
        int leftVal = (j-1 < 0) ? -1 : board->getValue(i, j-1);
        if (leftVal == 0 || abs(value-leftVal) == 1) {
            return true;
        } 
    }

    return false;
}

void numbrix::HybridNumbrixSolver::insertValue(const int &i, const int &j, const int &value)
{
    board->setValue(i, j, value);
    locations.insert({value, {i, j}});
    valuesInBoard.insert(value);
}

bool numbrix::HybridNumbrixSolver::empty(const int &i, const int &j)
{
    if (i < 0 || i >= numRows || j < 0 || j >= numCols) {
        return false;
    }
    return board->getValue(i, j) == 0;
}

bool numbrix::HybridNumbrixSolver::hasEmptyNeighbor(const int &i, const int &j)
{
    return (empty(i-1, j) || empty(i+1, j) || empty(i, j-1) || empty(i, j+2)); // compiler should optimize this so it returns true at the first empty cell
}

bool numbrix::HybridNumbrixSolver::solveSegment(const int &i, const int &j, const int &start, const int &current, const int &target, const Direction &from)
{
    if (current == target) {
        // load up the next segment and send
        auto nextSegment = segmentQueue.top();
        segmentQueue.pop();
        int nextStart = std::get<0>(nextSegment);
        auto [ni, nj] = locations[nextStart];
        if (!solveSegment(ni, nj, nextStart, nextStart, std::get<1>(nextSegment), NONE)) {
            // Put the following segment back on the stack and try again
            segmentQueue.push(nextSegment);
            return false;
        }
        else {
            return true;
        }
    }

    int upPriority, rightPriority, downPriority, leftPriority;
    switch (from) {
        case UP:
            upPriority = -1;
            break;
        case RIGHT:
            rightPriority = -1;
            break;
        case DOWN:
            downPriority = -1;
            break;
        case LEFT:
            leftPriority = -1;
            break;
    }

    
}

int numbrix::HybridNumbrixSolver::rankSegment(const int &start, const int &end)
{
    const auto [i, j] = locations[start];
    const auto [oi, oj] = locations[end];
    int distance = abs(i-oi) + abs(j-oj);
    int numSep = end-start;
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

    std::vector<std::tuple<int,int>> segments;
    for (auto item : positive) {
        int i;
        for (i = item+1; i < maxValue; i++) {
            if (hasValue(i)) {
                break;
            }
        }
        segments.push_back({item, i});
    }
    std::sort(segments.begin(), segments.end(), [=](const std::tuple<int,int> &a, const std::tuple<int,int> &b) {
        return rankSegment(std::get<0>(a), std::get<1>(a)) > rankSegment(std::get<0>(b), std::get<1>(b));
    });
    // add segments to queue
    std::cout << "Segments to be added" << std::endl;
    for (auto segment:segments) {
        std::cout << std::get<0>(segment) << " " << std::get<1>(segment) << std::endl;
        segmentQueue.push(segment);
    }
    auto startSegment = segmentQueue.top();
    segmentQueue.pop();
    int start = std::get<0>(startSegment);
    auto [i, j] = locations[start];
    bool result = solveSegment(i, j, start, start, std::get<1>(startSegment), NONE);
    maxValue = 0;
    valuesInBoard.clear();
    positive.clear();
    negative.clear();
    locations.clear();
    while (!segmentQueue.empty()) segmentQueue.pop();
    return result;
}
