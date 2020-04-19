#ifndef WARP_COORDINATE_H
#define WARP_COORDINATE_H

struct Coordinate {
    int x;
    int y;
};

inline bool operator==(const Coordinate& lhs, const Coordinate& rhs){
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

#endif  // WARP_COORDINATE_H
