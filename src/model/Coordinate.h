#ifndef WARP_COORDINATE_H
#define WARP_COORDINATE_H

#include <iostream>

struct Coordinate {
    friend std::ostream& operator<<(std::ostream& os, const Coordinate& coordinate) {
        os << coordinate.x << " " << coordinate.y;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Coordinate& coordinate) {
        is >> coordinate.x >> coordinate.y;
        return is;
    }

    bool operator==(const Coordinate& rhs) const { return x == rhs.x && y == rhs.y; }

    bool operator!=(const Coordinate& rhs) const { return !(rhs == *this); }

    int x;
    int y;
};

#endif  // WARP_COORDINATE_H
