#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#include <ostream>

namespace geometry {
    
/**
 * @brief A vector in 2D space.
 * @tparam T The data type of the coordinates of the vector.
*/
template<typename T>
struct Vec2 {
    T x,y;

    Vec2(const T& x, const T& y) : x(x), y(y) {}
    Vec2(const Vec2<T>& other) : x(other.x), y(other.y) {}
    bool operator==(const Vec2<T>& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Vec2<T>& other) const { return !operator==(other); }
    Vec2<T> operator+(const Vec2<T>& other) const { return Vec2<T>(x + other.x, y + other.y); }
    Vec2<T> operator-(const Vec2<T>& other) const { return Vec2<T>(x - other.x, y - other.y); }
    T operator*(const Vec2<T>& other) const { return x * other.x + y * other.y; }
    Vec2<T> operator*(const T& scalar) const { return Vec2<T>(scalar * x, scalar.y); }
    Vec2<T> operator/(const T& scalar) const { return Vec2<T>(x / scalar, y / scalar); }
    Vec2<T> operator+=(const Vec2<T>& other) {
        x += other.x; y += other.y;
        return *this;
    }
    Vec2<T> operator-=(const Vec2<T>& other) {
        x -= other.x; y -= other.y;
        return *this;
    }
    Vec2<T> operator*=(const T& scalar) {
        x *= scalar; y *= scalar;
        return *this;
    }
    Vec2<T> operator/=(const T& scalar) {
        x /= scalar; y /= scalar;
        return *this;
    }
    T magnitude() const { return sqrt(x*x + y*y); }
    Vec2<T> normalise() const { return *this / magnitude(); }
    T angle(const Vec2<T>& other) const {
        return acos(*this * other / magnitude() * other.magnitude());
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vec2<T>& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

typedef Vec2<int> IVec2;
typedef Vec2<long> LVec2;
typedef Vec2<long long> LLVec2;
typedef Vec2<float> FVec2;
typedef Vec2<double> DVec2;

} // namespace geometry

#endif // VEC2_H
