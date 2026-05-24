#include <RecursiveNumbrixSolver.h>

int numbrix::NumbrixSolver::getValue(const int &row, const int &column)
{
    numberOfReads++;
    return board.getValue(row, column);
}

void numbrix::NumbrixSolver::setValue(const int &row, const int &column, const int &value)
{
    numberOfWrites++;
    board.setValue(row, column, value);
}

bool numbrix::NumbrixSolver::hasValue(const int &value) const
{
    auto iter = valuesInBoard.find(value);
    return iter != valuesInBoard.end();
}

bool numbrix::NumbrixSolver::decendingRecSolver(const int &i, const int &j, const int &value)
{
    if (i < 0 || i >= numRows || j < 0 || j >= numCols) return false;

    int currentResident = getValue(i, j);
    if (currentResident != 0 && currentResident != value) return false;

    if (currentResident == 0) {
        setValue(i, j, value);
    }

    if (value == 1) {
        if (!accendingRecSolver(i, j, value)) {
            if (currentResident == 0) {
                setValue(i, j, currentResident);
            }
            return false;
        }
        return true;
    }
    else {
        if (decendingRecSolver(i-1, j, value-1) || decendingRecSolver(i+1, j, value-1) || decendingRecSolver(i, j-1, value-1) || decendingRecSolver(i, j+1, value-1)) {
            return true;
        }
        else {
            if (currentResident == 0) {
                setValue(i, j, currentResident);
            }
            return false;
        }
    }

}

bool numbrix::NumbrixSolver::accendingRecSolver(const int &i, const int &j, const int &value)
{
    if (i < 0 || i >= numRows || j < 0 || j >= numCols) return false;

    int currentValue = getValue(i, j);
    if (currentValue != 0 && currentValue != value) return false;

    if (currentValue == 0) {
        if (hasValue(value)) return false;

        setValue(i, j, value);
        valuesInBoard.insert(value);
    }

    if (value == maxValue) return true;

    // bool hasNeighbor = false;
    // bool lookForward = false;

    if (accendingRecSolver(i-1, j, value+1) || accendingRecSolver(i+1, j, value+1) || accendingRecSolver(i, j-1, value+1) || accendingRecSolver(i, j+1, value+1)) {
        return true;
    }
    else {
        if (currentValue == 0) {
            setValue(i, j, currentValue);
            valuesInBoard.erase(valuesInBoard.find(value));
        }
        return false;
    }
}

numbrix::NumbrixSolver::NumbrixSolver(const NumbrixBoard &board) : originalBoard(board), board(board)
{
    numRows = board.getNumRows();
    numCols = board.getNumCols();
}

bool numbrix::NumbrixSolver::solveRecursively()
{
    int minValue = numRows * numCols;
    maxValue = minValue;
    int x = 0;
    int y = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            numberOfReads++;
            int value = board.getValue(i, j);
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
    if (minValue == 1) {
        return accendingRecSolver(x, y, minValue);
    }
    else {
        return decendingRecSolver(x, y, minValue);
    }
}

int numbrix::NumbrixSolver::getNumberOfReads()
{
    return numberOfReads;
}

int numbrix::NumbrixSolver::getNumberOfWrites()
{
    return numberOfWrites;
}

void numbrix::NumbrixSolver::resetBoard()
{
    board.copyBoard(originalBoard);
    numberOfReads = 0;
    numberOfWrites = 0;
    valuesInBoard.clear();
}

std::string numbrix::NumbrixSolver::getBoard()
{
    return board.toString();
}
