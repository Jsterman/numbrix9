#include "NumbrixBoard.h"
#include <vector>
#include <fstream>

numbrix::NumbrixBoard::NumbrixBoard()
{

}

numbrix::NumbrixBoard::NumbrixBoard(std::string filename):NumbrixBoard()
{
    readPuzzle(filename);
}

int numbrix::NumbrixBoard::getValue(const int &i, const int &j)
{
    numberOfAccesses++;
    return board[i][j];
}

void numbrix::NumbrixBoard::readPuzzle(std::string filename)
{
    numberOfAccesses = 0;
    std::vector<std::vector<int>> vectorBoard;
    std::string line;
    std::ifstream fs(filename);
    
}
