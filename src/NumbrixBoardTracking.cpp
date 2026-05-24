#include "NumbrixBoardTracking.h"

int numbrix::NumbrixBoardTracking::getValue(const int &row, const int &column)
{
    numberOfReads++;
    NumbrixBoard::getValue(row, column);
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
