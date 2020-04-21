#ifndef WARP_COORDINATE_H
#define WARP_COORDINATE_H

#include <iostream>

struct Coordinate {
    friend std::ostream& operator<<(std::ostream& os,const Coordinate& coordinate) {
        os << coordinate.x << " " << coordinate.y;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Coordinate& coordinate) {
        is >> coordinate.x >> coordinate.y;
        return is;
    }

    int x;
    int y;
};

inline bool operator==(const Coordinate& lhs, const Coordinate& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator!=(const Coordinate& lhs, const Coordinate& rhs) {
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

#endif  // WARP_COORDINATE_H
