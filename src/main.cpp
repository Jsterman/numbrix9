#include <NumbrixBoard.h>
#include <iostream>

using namespace numbrix;

int main() {
    NumbrixBoard board("puzzles/simple_4x4.csv");
    std::cout << "This is the puzzle loaded:" << std::endl;
    std::cout << board.toString();
}