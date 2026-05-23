#include <string>
#include <stdexcept>

namespace numbrix {
    
class BadPuzzleFormatException: public std::runtime_error {
public:
    explicit BadPuzzleFormatException(const std::string &message) : std::runtime_error("Improper file format: "+message) {}
};

class NumbrixBoard {
private:
    int** board = nullptr;
    int** backupBoard = nullptr;
    int numberOfReads = 0;
    int numberOfWrites = 0;
    int numRows;
    int numColumns;
public:
    NumbrixBoard();
    NumbrixBoard(std::string filename);
    ~NumbrixBoard();
    int getValue(const int &row, const int &column);
    void setValue(const int &row, const int &column, const int &value);
    void readPuzzle(std::string filename);
    void resetPuzzle();
    int getNumberOfReads();
    int getNumberOfWrites();

    std::string toString();
};

}