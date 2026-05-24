#pragma once
#include <NumbrixBoard.h>

namespace numbrix {

class NumbrixBoardTracking: public NumbrixBoard {
private:
    int numberOfReads;
    int numberOfWrites;

public:
    NumbrixBoardTracking();
    int getValue(const int &row, const int &column);
    void setValue(const int &row, const int &column, const int &value);
    int getNumberOfReads() const;
    int getNumberOfWrites() const;
};

}