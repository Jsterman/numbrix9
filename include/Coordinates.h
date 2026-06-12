#pragma once
#include <iostream>

namespace numbrix {

enum Direction {
    NONE=-1,
    UP,
    RIGHT,
    DOWN,
    LEFT
};

struct Coordinates {
    int x;
    int y;
    Coordinates(): x(0), y(0) {}
    Coordinates(int x, int y) : x(x), y(y) {}
    Coordinates getCoordinatesUp() const {
        return Coordinates(x-1, y);
    }
    Coordinates getCoordinatesDown() const {
        return Coordinates(x+1, y);
    }
    Coordinates getCoordinatesLeft() const {
        return Coordinates(x,y-1);
    }
    Coordinates getCoordinatesRight() const {
        return Coordinates(x, y+1);
    }
    Coordinates getCoordinatesInDirection(const Direction& d) const {
        switch (d) {
            case UP:
            return {x-1,y};
            case DOWN:
            return {x+1,y};
            case LEFT:
            return {x,y-1};
            case RIGHT:
            return {x,y+1};
            default:
            return {x,y};
        }
    }
    bool operator==(const Coordinates &b) const {
        return x == b.x && y == b.y;
    }
    bool operator!=(const Coordinates &b) const {
        return x != b.x || y != b.y;
    }
    friend std::ostream& operator<<(std::ostream& os, const Coordinates& c) {
        return os << "(" << c.x << "," << c.y << ")";
    }
    static int getDistanceBetweenCoordinates(const Coordinates &one, const Coordinates &other) {
        return abs(one.x - other.x) + abs(one.y - other.y);
    }
};

}
// This part is so that we can use Coordinates in structures that require hashing (e.g. unsorted_set and unordered_map)
namespace std {
    template<>
    struct hash<numbrix::Coordinates> {
        inline std::size_t operator()(const numbrix::Coordinates& c) const noexcept {
            std::size_t h1 = std::hash<int>{}(c.x);
            std::size_t h2 = std::hash<int>{}(c.y);
            return h1^(h2<<1);
        }
    };
}