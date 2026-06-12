#include "../include/NumbrixBoard.h"
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include "NumbrixBoard.h"
#include <iostream>


numbrix::NumbrixBoard::NumbrixBoard() {}

numbrix::NumbrixBoard::NumbrixBoard(std::string filename):NumbrixBoard()
{
    readBoardFromFile(filename);
}

numbrix::NumbrixBoard::NumbrixBoard(const NumbrixBoard &old)
{
    copyBoard(old);
}

numbrix::NumbrixBoard::~NumbrixBoard()
{
    if (board == nullptr) return;

    for (int i = 0; i < numRows; i++) {
        delete[] board[i];
    }
    delete[] board;
}
int numbrix::NumbrixBoard::getValue(const Coordinates& c)
{
    if (board == nullptr) return -1;
    return board[c.x][c.y];
}

void numbrix::NumbrixBoard::setValue(const Coordinates& c, const int &value)
{
    if (board == nullptr) return;
    board[c.x][c.y] = value;
}

void numbrix::NumbrixBoard::readBoardFromFile(const std::string &filename)
{
    if (board != nullptr) {
        for (int i = 0; i < numRows; i++) {
            delete[] board[i];
        }
        delete[] board;
        board = nullptr;
    }
    std::vector<std::vector<int>> vectorBoard;
    std::string line;
    std::string item;
    std::ifstream fs(filename);
    if (!fs.good()) return;
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
        vectorBoard.push_back(row);
    }
    int rows = vectorBoard.size();

    board = new int*[rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new int[columns];
        for (int j = 0; j < columns; j++) {
            board[i][j] = vectorBoard[i][j];
        }
    }

    numRows = rows;
    numColumns = columns;
}

void numbrix::NumbrixBoard::copyBoard(const NumbrixBoard &other)
{
    if (other.board != nullptr) {
        if (numRows == other.numRows && numColumns == other.numColumns) {
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numColumns; j++) {
                    board[i][j] = other.board[i][j];
                }
            }
        }
        else {
            if (board != nullptr) {
                for (int i = 0; i < numRows; i++) {
                    delete[] board[i];
                }
                delete[] board;
            }

            numRows = other.numRows;
            numColumns = other.numColumns;

            board = new int*[numRows];
            for (int i = 0; i < numRows; i++) {
                board[i] = new int[numColumns];
                for (int j = 0; j < numColumns; j++) {
                    board[i][j] = other.board[i][j];
                }
            }
        }
    }
}

int numbrix::NumbrixBoard::getNumRows() const
{
    return numRows;
}

int numbrix::NumbrixBoard::getNumCols() const
{
    return numColumns;
}

std::string numbrix::NumbrixBoard::toString() const
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
                    oss << std::setw(numSpaces-rightpadding) << number;
                    oss << std::setw(rightpadding) << "";
                }
                else {
                    oss << number;
                }
            }
            if (j < numColumns-1) 
            {
                oss << " ";
            }
        }
        if (i < numRows-1) oss << "\n";
    }
    return oss.str();
}
