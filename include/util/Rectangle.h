#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"
#include <stdexcept>

namespace util {
    
/**
 * @brief A rectangle in 2D space.
 * @tparam T The data type of the coordinates of the rectangle.
*/
template<typename T>
class Rectangle {
private:
    Point<T> from, to;
public:
    /**
     * @brief Constructs a new Rectangle object.
     * @param from The top-left corner of the rectangle.
     * @param to The bottom-right corner of the rectangle.
     * @throws std::invalid_argument If the from point is not above and to the left of the to point.
    */
    Rectangle(const Point<T>& from, const Point<T>& to) : from(from), to(to) {
        if(from.x > to.x || from.y > to.y) {
            throw std::invalid_argument("Invalid rectangle bounds");
        }
    }
    /**
     * @brief Constructs a new Rectangle object.
     * @param x1 The x-coordinate of the top-left corner of the rectangle.
     * @param y1 The y-coordinate of the top-left corner of the rectangle.
     * @param x2 The x-coordinate of the bottom-right corner of the rectangle.
     * @param y2 The y-coordinate of the bottom-right corner of the rectangle.
     * @throws std::invalid_argument If the from point is not above and to the left of the to point.
    */
    Rectangle(const T& x1, const T& y1, const T& x2, const T& y2)
        : from(x1, y1)
        , to(x2, y2) 
    {
        if(from.x > to.x || from.y > to.y) {
            throw std::invalid_argument("Invalid rectangle bounds");
        }
    }
    /**
     * @brief Constructs a new Rectangle object.
     * @param position The top-left corner of the rectangle.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     * @throws std::invalid_argument If the width or height is negative.
    */
    Rectangle(const Point<T>& position, const T& width, const T& height)
        : from(position)
        , to(position + Point<T>(width, height)) 
    {
        if(from.x > to.x || from.y > to.y) {
            throw std::invalid_argument("Invalid rectangle bounds");
        }
    }
    
    bool operator==(const Rectangle<T>& other) const {
        return from == other.from && to == other.to;
    }
    bool operator!=(const Rectangle<T>& other) const { return !operator==(other); }

    /**
     * @brief Checks if a point is inside the rectangle.
    */
    bool contains(const Point<T>& point) const {
        return point.x >= from.x 
            && point.y >= from.y
            && point.x <= to.x
            && point.y <= to.y;
    }
    /**
     * @brief Checks if a point is strictly inside the rectangle.
    */
    bool containsStrictly(const Point<T>& point) const {
        return point.x > from.x 
            && point.y > from.y
            && point.x < to.x
            && point.y < to.y;
    }
    /**
     * @brief Checks if this rectangle intersects another.
    */
    bool intersects(const Rectangle<T>& other) const {
        if(other.from.x > to.x || other.from.y > to.y) {
            return false;
        }
        else {
            return other.to.x >= from.x && other.to.y >= from.y;
        }
    }
    /**
     * @brief Moves the rectangle by the given amount.
    */
    void move(T x, T y) {
        from.x += x; from.y += y;
        to.x += x; to.y += y;
    }
    /**
     * Mirror the rectangle along a given x-axis.
     * @param axis The x-coordinate of the axis of symmetry.
    */
    void mirrorX(T axis) {
        from.x = 2 * axis - from.x;
        to.x = 2 * axis - to.x;
    }
    /**
     * Mirror the rectangle along a given y-axis.
     * @param axis The y-coordinate of the axis of symmetry.
    */
    void mirrorY(T axis) {
        from.y = 2 * axis - from.y;
        to.y = 2 * axis - to.y;
    }

    const Point<T>& getFrom() const { return from; }
    const Point<T>& getTo() const { return to; }
    T getWidth() const { return to.x - from.x; }
    T getHeight() const { return to.y - from.y; }
    T getArea() const { return getWidth() * getHeight(); }
    T getPerimeter() const { return 2 * (getWidth() + getHeight()); }
};

typedef Rectangle<int> IRectangle;
typedef Rectangle<long> LRectangle;
typedef Rectangle<long long> LLRectangle;
typedef Rectangle<float> FRectangle;
typedef Rectangle<double> DRectangle;

} // namespace util

#endif // RECTANGLE_H
