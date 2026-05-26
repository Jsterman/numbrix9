#include "NumbrixBoardTracking.h"

numbrix::NumbrixBoardTracking::NumbrixBoardTracking(std::string filename) : NumbrixBoard(filename)
{
}

int numbrix::NumbrixBoardTracking::getValue(const int &row, const int &column)
{
    numberOfReads++;
    return NumbrixBoard::getValue(row, column);
}

void numbrix::NumbrixBoardTracking::setValue(const int &row, const int &column, const int &value)
{
    numberOfWrites++;
    NumbrixBoard::setValue(row, column, value);
}

int numbrix::NumbrixBoardTracking::getNumberOfReads() const
{
    return numberOfReads;
}

int numbrix::NumbrixBoardTracking::getNumberOfWrites() const
{
    return numberOfWrites;
}

void numbrix::NumbrixBoardTracking::resetTracking()
{
    numberOfReads = 0;
    numberOfWrites = 0;
}
