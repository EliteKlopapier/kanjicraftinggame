#ifndef POINT_H
#define POINT_H

namespace util {
    
/**
 * @brief A point in 2D space.
 * @tparam T The data type of the coordinates of the point.
*/
template<typename T>
struct Point {
    T x,y;

    Point(const T& x, const T& y) : x(x), y(y) {}
    Point(const Point<T>& other) : x(other.x), y(other.y) {}
    bool operator==(const Point<T>& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Point<T>& other) const { return !operator==(other); }
    Point<T> operator+(const Point<T>& other) { return Point<T>(x + other.x, y + other.y); }
    Point<T> operator-(const Point<T>& other) { return Point<T>(x - other.x, y - other.y); }
    Point<T> operator+=(const Point<T>& other) {
        x += other.x; y += other.y;
        return *this;
    }
    Point<T> operator-=(const Point<T>& other) {
        x -= other.x; y -= other.y;
        return *this;
    }
};

typedef Point<int> IPoint;
typedef Point<long> LPoint;
typedef Point<long long> LLPoint;
typedef Point<float> FPoint;
typedef Point<double> DPoint;

} // namespace util

#endif // POINT_H
