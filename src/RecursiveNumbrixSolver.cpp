#include <RecursiveNumbrixSolver.h>

bool numbrix::RecursiveNumbrixSolver::hasValue(const int &value) const
{
    auto iter = valuesInBoard.find(value);
    return iter != valuesInBoard.end();
}

bool numbrix::RecursiveNumbrixSolver::decendingRecSolver(const int &i, const int &j, const int &value, const Direction &from)
{
    if (i < 0 || i >= numRows || j < 0 || j >= numCols) return false;

    int currentResident = board->getValue(i, j);
    if (currentResident != 0 && currentResident != value) return false;

    if (currentResident == 0) {
        board->setValue(i, j, value);
    }

    if (value == 1) {
        if (!accendingRecSolver(i, j, value, NONE)) {
            if (currentResident == 0) {
                board->setValue(i, j, currentResident);
            }
            return false;
        }
        return true;
    }
    else {
        if (from != UP && decendingRecSolver(i-1, j, value-1, DOWN)) {
            return true;
        }
        else if (from != DOWN && decendingRecSolver(i+1, j, value-1, UP)) {
            return true;
        }
        else if (from != LEFT && decendingRecSolver(i, j-1, value-1, RIGHT)) {
            return true;
        }
        else if (from != RIGHT && decendingRecSolver(i, j+1, value-1, LEFT)) {
            return true;
        }
        else {
            if (currentResident == 0) {
                board->setValue(i, j, currentResident);
            }
            return false;
        }
    }

}

bool numbrix::RecursiveNumbrixSolver::accendingRecSolver(const int &i, const int &j, const int &value, const Direction &from)
{
    int currentValue = board->getValue(i, j);
    if (currentValue != 0 && currentValue != value) return false;

    if (currentValue == 0) {
        if (hasValue(value)) return false;

        board->setValue(i, j, value);
        valuesInBoard.insert(value);
    }

    if (value == maxValue) return true;

    if (from != UP && i-1 >= 0 && accendingRecSolver(i-1, j, value+1, DOWN)) {
        return true;
    }
    else if (from != DOWN && i+1 < numRows && accendingRecSolver(i+1, j, value+1, UP)) {
        return true;
    }
    else if (from != LEFT && j-1 >= 0 && accendingRecSolver(i, j-1, value+1, RIGHT)) {
        return true;
    }
    else if (from != RIGHT && j+1 < numCols && accendingRecSolver(i, j+1, value+1, LEFT)) {
        return true;
    }
    else {
        if (currentValue == 0) {
            board->setValue(i, j, currentValue);
            valuesInBoard.erase(valuesInBoard.find(value));
        }
        return false;
    }
}

numbrix::RecursiveNumbrixSolver::RecursiveNumbrixSolver()
{
}

bool numbrix::RecursiveNumbrixSolver::solve(NumbrixBoard *board)
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
                valuesInBoard.insert(value);
            }
        }
    }
    bool result;
    if (minValue == 1) {
        result = accendingRecSolver(x, y, minValue, NONE);
    }
    else {
        result = decendingRecSolver(x, y, minValue, NONE);
    }
    maxValue = 0;
    valuesInBoard.clear();
    return result;
}
