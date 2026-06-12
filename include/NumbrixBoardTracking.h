#pragma once
#include <NumbrixBoard.h>

namespace numbrix {

class NumbrixBoardTracking: public NumbrixBoard {
private:
    int numberOfReads;
    int numberOfWrites;

public:
    NumbrixBoardTracking(std::string filename);
    int getValue(const Coordinates &c);
    void setValue(const Coordinates &c, const int &value);
    int getNumberOfReads() const;
    int getNumberOfWrites() const;
    void resetTracking();
};

}