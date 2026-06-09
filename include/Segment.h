#include <iostream>

namespace numbrix {

struct Segment {
    int startVal;
    int endVal;
    Segment(): startVal(0), endVal(0) {}
    Segment(int x, int y) : startVal(x), endVal(y) {}
    bool operator==(const Segment &b) const {
        return startVal == b.startVal && endVal == b.endVal;
    }
    bool operator!=(const Segment &b) const {
        return startVal != b.startVal || endVal != b.endVal;
    }
    friend std::ostream& operator<<(std::ostream& os, const Segment& c) {
        return os << "(" << c.startVal << "," << c.endVal << ")";
    }
    static int getDistanceBetweenCoordinates(const Segment &one, const Segment &other) {
        return abs(one.startVal - other.startVal) + abs(one.endVal - other.endVal);
    }
};

}
// This part is so that we can use Coordinates in structures that require hashing (e.g. unsorted_set and unordered_map)
namespace std {
    template<>
    struct hash<numbrix::Segment> {
        inline std::size_t operator()(const numbrix::Segment& c) const noexcept {
            std::size_t h1 = std::hash<int>{}(c.startVal);
            std::size_t h2 = std::hash<int>{}(c.endVal);
            return h1^(h2<<1);
        }
    };
}