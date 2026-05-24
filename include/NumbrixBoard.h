#pragma once
#include <string>
#include <stdexcept>

namespace numbrix {
    
class BadPuzzleFormatException: public std::runtime_error {
public:
    explicit BadPuzzleFormatException(const std::string &message) : std::runtime_error("Improper file format: "+message) {}
};

class NumbrixBoard {
protected:
    int** board = nullptr;
    int numRows = 0;
    int numColumns = 0;
public:
    NumbrixBoard();
    NumbrixBoard(std::string filename);
    NumbrixBoard(const NumbrixBoard&);
    ~NumbrixBoard();
    virtual int getValue(const int &row, const int &column);
    virtual void setValue(const int &row, const int &column, const int &value);
    void readBoardFromFile(const std::string &filename);
    void copyBoard(const NumbrixBoard &other);

    int getNumRows() const;
    int getNumCols() const;

    std::string toString() const;
};

}