#include <NumbrixSolver.h>

namespace numbrix {
std::string toString(Direction d){
    switch (d) {
        case UP:
        return "UP";
        case DOWN:
        return "DOWN";
        case LEFT:
        return "LEFT";
        case RIGHT:
        return "RIGHT";
        default:
        return "NONE";
    }
}
Direction reverseDirection(Direction d)
{
    switch (d) {
        case UP:
        return DOWN;
        case DOWN:
        return UP;
        case LEFT:
        return RIGHT;
        case RIGHT:
        return LEFT;
        default:
        return NONE;
    }
}
}