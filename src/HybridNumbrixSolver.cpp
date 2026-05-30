#include <HybridNumbrixSolver.h>
#include <iostream>



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
            }

            if (foundSpot) {
                insertValue(nexti, nextj, nextValue);
                otherList->erase(otherList->find(twoAfter));
                it = thisList->erase(it);
                changed = true;
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
                continue;
            }
        }
        ++it;
    }
    return changed;
}

void numbrix::HybridNumbrixSolver::insertValue(const int &i, const int &j, const int &value)
{
    board->setValue(i, j, value);
    locations.insert({value, {i, j}});
    valuesInBoard.insert(value);
}

bool numbrix::HybridNumbrixSolver::empty(int i, int j)
{
    if (i < 0 || i >= numRows || j < 0 || j >= numCols) {
        return false;
    }
    return board->getValue(i, j) == 0;
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

    bool result;
    if (minValue == 1) {
        result = accendingRecSolver(x, y, minValue);
    }
    else {
        result = decendingRecSolver(x, y, minValue);
    }
    maxValue = 0;
    valuesInBoard.clear();
    positive.clear();
    negative.clear();
    locations.clear();
    return result;
}
