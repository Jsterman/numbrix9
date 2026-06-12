#include <RecursiveNumbrixSolver.h>

bool numbrix::RecursiveNumbrixSolver::hasValue(const int &value) const
{
    auto iter = valuesInBoard.find(value);
    return iter != valuesInBoard.end();
}

bool numbrix::RecursiveNumbrixSolver::decendingRecSolver(const Coordinates& c, const int &value, const Direction &from)
{
    if (c.x < 0 || c.x >= numRows || c.y < 0 || c.y >= numCols) return false;

    int currentResident = board->getValue(c);
    if (currentResident != 0 && currentResident != value) return false;

    if (currentResident == 0) {
        board->setValue(c, value);
    }

    if (value == 1) {
        if (!accendingRecSolver(c, value, NONE)) {
            if (currentResident == 0) {
                board->setValue(c, currentResident);
            }
            return false;
        }
        return true;
    }
    else {
        if (from != UP && decendingRecSolver(c.getCoordinatesUp(), value-1, DOWN)) {
            return true;
        }
        else if (from != DOWN && decendingRecSolver(c.getCoordinatesDown(), value-1, UP)) {
            return true;
        }
        else if (from != LEFT && decendingRecSolver(c.getCoordinatesLeft(), value-1, RIGHT)) {
            return true;
        }
        else if (from != RIGHT && decendingRecSolver(c.getCoordinatesRight(), value-1, LEFT)) {
            return true;
        }
        else {
            if (currentResident == 0) {
                board->setValue(c, currentResident);
            }
            return false;
        }
    }

}

bool numbrix::RecursiveNumbrixSolver::accendingRecSolver(const Coordinates& c, const int &value, const Direction &from)
{
    int currentValue = board->getValue(c);
    if (currentValue != 0 && currentValue != value) return false;

    if (currentValue == 0) {
        if (hasValue(value)) return false;

        board->setValue(c, value);
        valuesInBoard.insert(value);
    }

    if (value == maxValue) return true;

    if (from != UP && c.x-1 >= 0 && accendingRecSolver(c.getCoordinatesUp(), value+1, DOWN)) {
        return true;
    }
    else if (from != DOWN && c.x+1 < numRows && accendingRecSolver(c.getCoordinatesDown(), value+1, UP)) {
        return true;
    }
    else if (from != LEFT && c.y-1 >= 0 && accendingRecSolver(c.getCoordinatesLeft(), value+1, RIGHT)) {
        return true;
    }
    else if (from != RIGHT && c.y+1 < numCols && accendingRecSolver(c.getCoordinatesRight(), value+1, LEFT)) {
        return true;
    }
    else {
        if (currentValue == 0) {
            board->setValue(c, currentValue);
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
            int value = board->getValue({i, j});
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
        result = accendingRecSolver({x, y}, minValue, NONE);
    }
    else {
        result = decendingRecSolver({x, y}, minValue, NONE);
    }
    maxValue = 0;
    valuesInBoard.clear();
    return result;
}
