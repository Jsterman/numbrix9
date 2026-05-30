#include <HybridNumbrixSolver.h>
#include <RecursiveNumbrixSolver.h>
#include <NumbrixBoardTracking.h>
#include <iostream>
#include <chrono>

using namespace numbrix;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(int argc, char *argv[]) {
    std::string filename = "puzzles/easy_may_19_2026.csv";
    if (argc > 1) {
        filename = std::string(argv[1]);
    }
    NumbrixBoardTracking* originalBoard = new NumbrixBoardTracking(filename);
    NumbrixBoardTracking* board = new NumbrixBoardTracking(*originalBoard);
    std::cout << "This is the puzzle loaded (" << filename << "):" << std::endl;
    std::cout << board->toString() << std::endl<< std::endl;

    std::cout << "Solving Recursively..." << std::endl << std::endl;
    HybridNumbrixSolver solver;
    auto t1 = high_resolution_clock::now();
    bool solutionFound = solver.solve(board);
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms = t2-t1;
    if (solutionFound) {
        std::cout << "Solution Found!\n" << board->toString() << std::endl;
        std::cout << "Duration: " << ms.count() << "ms\n";
        std::cout << "Number of reads: " << board->getNumberOfReads() << std::endl;
        std::cout << "Number of writes: " << board->getNumberOfWrites() << std::endl << std::endl;

        double runningTotal = ms.count();

        std::cout << "Averaging the time to solve over 9 additional runs..." << std::endl << std::endl;

        for (int i = 0; i < 9; i++) {
            board->resetTracking();
            board->copyBoard(*originalBoard);
            auto t1 = high_resolution_clock::now();
            bool solutionFound = solver.solve(board);
            auto t2 = high_resolution_clock::now();
            duration<double, std::milli> ms = t2-t1;
            runningTotal += ms.count();
            std::cout << "Run " << i+2 << " Complete" << std::endl;
        }

        std::cout << std::endl << "Average time to solve: " << runningTotal/10 << "ms" << std::endl;
    }
    else {
        std::cout << "No solution found..." << std::endl;
    }

}