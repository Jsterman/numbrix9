#include "NumbrixBoardTracking.h"

numbrix::NumbrixBoardTracking::NumbrixBoardTracking(std::string filename) : NumbrixBoard(filename)
{
    numberOfReads = 0;
    numberOfWrites = 0;
}

int numbrix::NumbrixBoardTracking::getValue(const Coordinates &c)
{
    numberOfReads++;
    return NumbrixBoard::getValue(c);
}

void numbrix::NumbrixBoardTracking::setValue(const Coordinates &c, const int &value)
{
    numberOfWrites++;
    NumbrixBoard::setValue(c, value);
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
