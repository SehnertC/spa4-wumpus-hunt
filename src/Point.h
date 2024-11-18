//
// Created by sehnertc on 11/14/2024.
//

#ifndef POINT_H
#define POINT_H
#include <map>

struct Point{
  int x;
  int y;

  Point(int x = 0, int y = 0) {
    this->x = x;
    this->y = y;
  }

  Point operator+(const Point& other) const {
    return {x + other.x, y + other.y};
  }

  Point operator-(const Point& other) const {
    return {x - other.x, y - other.y};
  }

  Point operator-() const {
    return {-x, -y};
  }

  Point operator*(const int other) const {
    return {x * other, y * other};
  }

  Point operator/(const int other) const {
    return {x / other, y / other};
  }

  bool operator==(const Point & point) const {
    return x == point.x && y == point.y;
  }

  static const std::map<char, Point> directions;
};

#endif