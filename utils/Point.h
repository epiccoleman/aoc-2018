#ifndef POINT_H
#define POINT_H

namespace utils {
  struct Point {
    int x;
    int y;

    Point operator+(const Point& a){
      return { a.x + x, a.y + y};
    }

    Point& operator+=(const Point& a){
      this->x += a.x;
      this->y += a.y;
      return *this;
    }

    bool operator ==(const Point &rhs) const {
      return this->x == rhs.x && this->y == rhs.y;
    }
  };
}

#endif
