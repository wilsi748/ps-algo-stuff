#ifndef POINT2D_H
#define POINT2D_H

#include <cmath>
#include <iostream>
#include <type_traits>
#include <vector> 
#include <algorithm>

using namespace std;

template<typename T>
class Point2D {
    static_assert(is_arithmetic<T>::value, "Only numbers");

public:
    Point2D() : _x(0), _y(0) {}
    Point2D(T x, T y) : _x(x), _y(y) {}

    Point2D operator+(const Point2D& other) const;
    Point2D operator-(const Point2D& other) const;
    Point2D operator*(T scalar) const;
    Point2D operator/(T scalar) const;
    Point2D& operator+=(const Point2D<T>& other);
    Point2D& operator/=(T scalar);
    bool operator==(const Point2D& other) const;
    bool operator>(const Point2D<T>& other) const;
    bool operator<(const Point2D<T>& other) const;
    bool operator>=(const Point2D<T>& other) const;
    bool operator<=(const Point2D<T>& other) const;
    T operator*(const Point2D& other) const; // dot product or scalar product
    T operator^(const Point2D& other) const; // cross product or vector product
    double magnitude() const; // length of the vector
    double angle() const; // angle of vector with respect to x-axis in radians
    double angle(const Point2D& other) const; // angle between vector and other vector in radians
    double distance(const Point2D& other) const; // distance between two points 

    friend std::ostream& operator<<(std::ostream& os, const Point2D& point) {
        os << "(" << point._x << ", " << point._y << ")";
        return os;
    }
    // getter setter
    T x() const { return _x; }
    T y() const { return _y; }
    void set_x(T x) { _x = x; }
    void set_y(T y) { _y = y; }

private:
    mutable T _x, _y;
};

template<typename T>
Point2D<T> Point2D<T>::operator+(const Point2D& other) const {
    return Point2D(_x + other._x, _y + other._y);
}

template<typename T>
Point2D<T> Point2D<T>::operator-(const Point2D& other) const {
    return Point2D(_x - other._x, _y - other._y);
}

template<typename T>
Point2D<T> Point2D<T>::operator*(T scalar) const {
    return Point2D(_x * scalar, _y * scalar);
}

template<typename T>
Point2D<T> Point2D<T>::operator/(T scalar) const {
    return Point2D(_x / scalar, _y / scalar);
}

template<typename T>
bool Point2D<T>::operator==(const Point2D<T>& other) const {
    return _x == other._x && _y == other._y;
}

template <typename T>
bool Point2D<T>::operator>(const Point2D<T>& other) const {
    return (_x > other._x || (_x == other._x && _y > other._y));
}

template <typename T>
bool Point2D<T>::operator<(const Point2D<T>& other) const {
    return (_x < other._x || (_x == other._x && _y < other._y));
}

template <typename T>
bool Point2D<T>::operator>=(const Point2D<T>& other) const {
    return (_x >= other._x || (_x == other._x && _y >= other._y));
}

template <typename T>
bool Point2D<T>::operator<=(const Point2D<T>& other) const {
    return (_x <= other._x || (_x == other._x && _y <= other._y));
}

template<typename T>
Point2D<T>& Point2D<T>::operator+=(const Point2D& other) {
    _x += other._x;
    _y += other._y;
    return *this;
}

template<typename T>
Point2D<T>& Point2D<T>::operator/=(T scalar) {
    _x /= scalar;
    _y /= scalar;
    return *this;
}

template<typename T>
T Point2D<T>::operator*(const Point2D& other) const {
    return _x * other._x + _y * other._y;
}

template<typename T>
T Point2D<T>::operator^(const Point2D& other) const {
    return _x * other._y - _y * other._x;
}

template<typename T>
double Point2D<T>::magnitude() const {
    return sqrt(_x * _x + _y * _y);
}

template<typename T>
double Point2D<T>::angle() const {
    return atan2(_y, _x);
}

template<typename T>
double Point2D<T>::angle(const Point2D& other) const {
    return acos((*this * other) / (magnitude() * other.magnitude()));
}

template<typename T>
double Point2D<T>::distance(const Point2D& other) const {
    return (*this - other).magnitude();
}

template<typename T>
double slope(const Point2D<T>& p1, const Point2D<T>& p2) {
    return (p2.y() - p1.y()) / (p2.x() - p1.x());
}

// collinear: 0, clockwise: 1, counterclockwise: 2
template<typename T>
T orientation(const Point2D<T>& p1, const Point2D<T>& p2, const Point2D<T>& p3) {
    T cp = (p2 - p1) ^ (p3 - p2);
    if (cp == 0) return 0;
    return (cp > 0) ? 1 : 2;
}

// cross prod
template<typename T>
T cross_prod(const Point2D<T>& p1, const Point2D<T>& p2, const Point2D<T>& p3) {
    return (p2 - p1) ^ (p3 - p2);
}

template<typename T>
bool on_segment(const Point2D<T> p, const Point2D<T> p1, const Point2D<T> p2) {
    return (p.x() <= max(p1.x(), p2.x()) && p.x() >= min(p1.x(), p2.x()) &&
            p.y() <= max(p1.y(), p2.y()) && p.y() >= min(p1.y(), p2.y()));
}

template <typename T>
bool segments_overlap(Point2D<T> p1, Point2D<T> p2, Point2D<T> p3, Point2D<T> p4) {
    if (on_segment(p1, p2, p3) || on_segment(p1, p2, p4) || on_segment(p3, p4, p1) || on_segment(p3, p4, p2)) {
        return true;
    } else {
        return false;
    }
}

/* 
 * Calculates the area of a simple polygon with the Shoelace formula, also known as Gauss's area formula.
 * The Shoelace formula calculates the signed area of a polygon by summing the products of consecutive coordinates of the polygon's vertices.
 *
 * @param poly : a vector of points using the Point2D class forming a simple polygon.
 * 
 * Time complexity: O(n), where n is the number of points in the polygon.
 */
template<typename T>
T polygon_area(const vector<Point2D<T>>& poly) {
    T area = 0;
    for (int i = 0; i < poly.size(); i++) {
        T j = (i + 1) % poly.size();
        area += poly[i] ^ poly[j];
    }
    return area / 2.0;
}

/*
 * Determines the relative position of a point with respect to a polygon.
 *
 * @param p The point to be checked.
 * @param poly The polygon defined by a vector of 2D points.
 * @return 1 if the point is inside the polygon, -1 if it is outside, and 0 if it lies on an edge or vertex of the polygon.
 * 
 * Time complexity: O(n) where n is the number of vertexes.
 */
template<typename T>
T inside_poly(const Point2D<T>& p, const vector<Point2D<T>>& poly) {
    int n = poly.size();
    int cross = 0; // counter for number of intersections
    
    for(int i = 0; i < n; i++) {
        int j = (i + 1) % n; // next vertex, to be able to wrap around
        
        // check if the point p has the same coords as any point in the polygon.
        if (poly[i].x() == p.x() && poly[i].y() == p.y() || poly[j].x() == p.x() && poly[j].y() == p.y()) {
            return 0;
        }
        // checks if collinear and if point is on the line segment made by poly[i] and poly[j].
        if(orientation(p, poly[i], poly[j]) == 0 && on_segment(p, poly[i], poly[j])) {
            return 0;
        }
        
        // check boundaries for x
        bool cond1 = (poly[i].x() <= p.x()) && (p.x() < poly[j].x()); 
        bool cond2 = (poly[j].x() <= p.x()) && (p.x() < poly[i].x());
        // slope between polygon points
        double slope = static_cast<double>(poly[j].y() - poly[i].y()) / static_cast<double>(poly[j].x() - poly[i].x());
        // condition for checking if point is above polygon or not.
        bool above = (p.y() < slope * (p.x() - poly[i].x()) + poly[i].y());
        
        if((cond1 || cond2) && above) cross++;
    }

    if (cross % 2 != 0) {
        return 1;
    } else {
        return -1;
    }
}

template<typename T>
vector<Point2D<T>> intersection(Point2D<T> p1, Point2D<T> p2, Point2D<T> p3, Point2D<T> p4) {
    vector<Point2D<T>> res;
    T denom = ((p4.y() - p3.y()) * (p2.x() - p1.x())) - ((p4.x() - p3.x()) * (p2.y() - p1.y()));
    T nume_a = ((p4.x() - p3.x()) * (p1.y() - p3.y())) - ((p4.y() - p3.y()) * (p1.x() - p3.x()));
    T nume_b = ((p2.x() - p1.x()) * (p1.y() - p3.y())) - ((p2.y() - p1.y()) * (p1.x() - p3.x()));

    if (denom == 0) { // parallel or collinear
        if(nume_a == 0 && nume_b == 0) { // coincident
            if(p1 == p2) { 
                res.push_back(p1);
            } else {
                res.push_back(p1);
                res.push_back(p2);
            }
        } else { // collinear but non-overlapping
            // No intersection point
        }
    } else { // intersect
        T ua = nume_a / denom;
        T ub = nume_b / denom;
        if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
            T t = p1.x() + ua * (p2.x() - p1.x());
            T u = p1.y() + ua * (p2.y() - p1.y());
            Point2D<T> intersection_point(t, u);
            res.push_back(intersection_point);
        }
    }
    return res;
}

template<typename T>
vector<Point2D<T>> convex_hull(vector<Point2D<T>>& points) {
    // Find the point with the lowest y-coordinate
    int idx = 0;
    for (int i = 1; i < points.size(); i++) {
        if (points[i].y() < points[idx].y() || (points[i].y() == points[idx].y() && points[i].x() < points[idx].x())) {
            idx = i;
        }
    }
    Point2D<T> ref = points[idx];

    // Check for duplicate points
    sort(points.begin(), points.end(), [](const Point2D<T>& p1, const Point2D<T>& p2) {
        return p1.x() < p2.x() || (p1.x() == p2.x() && p1.y() < p2.y());
    });
    points.erase(unique(points.begin(), points.end()), points.end());

    // Sort the points based on their polar angle with respect to the reference point
    sort(points.begin(), points.end(), [&ref](Point2D<T> p1, Point2D<T> p2) {
        double d = cross_prod(ref, p1, p2);
        if (d == 0) {
            return (p1 - ref).magnitude() < (p2 - ref).magnitude();
        }
        return d > 0;
    });
    
    // Compute the convex hull using the Graham scan algorithm
    vector<Point2D<T>> hull;
    for (const auto& p : points) {
        while (hull.size() >= 2 && cross_prod(hull[hull.size() - 2], hull[hull.size() - 1], p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }
    return hull;
}

/*
 * Calculates the maxmimum number of colinear points.
 *
 * @param points : A vector of 2D points.
 * @param count : counts the max number of colinear points.
 * @param slope_tracker : keeps track of the number of points with a certain slope.
 * @return number of colinear points.
 * 
 * Time complexity: O(n^2) where n is the number of points.
 */
template<typename T>
int number_of_colinear_points(vector<Point2D<T>> points) {
    int count = 0;
    int n = points.size();
    for(int i = 0; i < n; i++) {
        map<double, int> slope_tracker;
        for(int j = i + 1; j < n; j++) {
            Point2D<T> p1 = points[i];
            Point2D<T> p2 = points[j];

            double slope = static_cast<double>(p2.y() - p1.y()) / static_cast<double>(p2.x() - p1.x());

            slope_tracker[slope]++;

            count = max(count, slope_tracker[slope]);
        }
    }
    return count + 1;
}


#endif // POINT2D_H
