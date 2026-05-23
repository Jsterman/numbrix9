#include "../include/NumbrixBoard.h"
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include "NumbrixBoard.h"


numbrix::NumbrixBoard::NumbrixBoard()
{

}

numbrix::NumbrixBoard::NumbrixBoard(std::string filename):NumbrixBoard()
{
    readPuzzle(filename);
}

numbrix::NumbrixBoard::~NumbrixBoard()
{
    if (board == nullptr) return;

    for (int i = 0; i < numRows; i++) {
        delete[] backupBoard[i];
        delete[] board[i];
    }
    delete[] backupBoard;
    delete[] board;
}
int numbrix::NumbrixBoard::getValue(const int &i, const int &j)
{
    if (board == nullptr) return -1;
    numberOfReads++;
    return board[i][j];
}

void numbrix::NumbrixBoard::setValue(const int &row, const int &column, const int &value)
{
    if (board == nullptr) return;
    numberOfWrites++;
    board[row][column] = value;
}

void numbrix::NumbrixBoard::readPuzzle(std::string filename)
{
    numberOfReads = 0;
    numberOfWrites = 0;
    std::vector<std::vector<int>> vectorBoard;
    std::string line;
    std::string item;
    std::ifstream fs(filename);
    std::istringstream ss;

    int columns = -1;

    while (getline(fs, line)) {
        std::vector<int> row;
        ss.clear();
        ss.str(line);

        while (getline(ss, item, ',')) {
            row.push_back(stoi(item));
        }
        if (columns == -1) {
            columns = row.size();
        }
        else if (columns != row.size())
        {
            std::ostringstream oss;
            oss << "Row " << vectorBoard.size()+1 << " has more items than the previous rows. Please correct.";
            throw BadPuzzleFormatException(oss.str());
        }
    }
    int rows = vectorBoard.size();

    backupBoard = new int*[rows];
    board = new int*[rows];
    for (int i = 0; i < rows; i++) {
        backupBoard[i] = new int[columns];
        board[i] = new int[columns];
        for (int j = 0; j < columns; j++) {
            backupBoard[i][j] = vectorBoard[i][j];
            board[i][j] = vectorBoard[i][j];
        }
    }

    numRows = rows;
    numColumns = columns;
}

void numbrix::NumbrixBoard::resetPuzzle()
{
    numberOfReads = 0;
    numberOfWrites = 0;
    if (board == nullptr || backupBoard == nullptr) return;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            board[i][j] = backupBoard[i][j];
        }
    }
}

int numbrix::NumbrixBoard::getNumberOfReads()
{
    return numberOfReads;
}

int numbrix::NumbrixBoard::getNumberOfWrites()
{
    return numberOfWrites;
}

std::string numbrix::NumbrixBoard::toString()
{
    if (board == nullptr) return "";
    std::ostringstream oss;
    int maxNumber = numRows * numColumns;
    int numSpaces = std::to_string(maxNumber).size();
    std::string underscores = "_";
    for (int i = 0; i < numSpaces-1; i++) underscores += "_";

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            if (board[i][j] == 0) {
                oss << underscores;
            }
            else {
                std::string number = std::to_string(board[i][j]);
                int padding = numSpaces - number.size();
                if (padding > 0) {
                    int rightpadding = padding / 2;
                    oss << std::setw(padding-rightpadding + number.size()) << number;
                    oss << std::setw(rightpadding) << "";
                }
            }
            if (j < numColumns-1) oss << " ";
        }
        if (i < numRows-1) oss << "\n";
    }
    return oss.str();
}
