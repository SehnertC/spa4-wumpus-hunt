//
// Created by sehnertc on 11/17/2024.
//

#include "Point.h"

const std::map<char, Point> Point::directions = {
    {'n', Point(0, -1)}, {'e', Point(1, 0)},
    {'s', Point(0, 1)}, {'w', Point(-1, 0)}
};