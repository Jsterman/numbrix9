#include <string>


namespace numbrix {
class NumbrixBoard {
private:
    int** board = nullptr;
    int numberOfAccesses = 0;
public:
    NumbrixBoard();
    NumbrixBoard(std::string filename);
    int getValue(const int &row, const int &column);
    void readPuzzle(std::string filename);
};
}