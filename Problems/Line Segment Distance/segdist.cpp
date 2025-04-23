/*
    Author: William Sid (wilsi748)

    Problem solved: Line Segment Distance

    Time complexity: O(1) for each min distance to compute.
*/
#include <bits/stdc++.h>
#include "../Point2D.h"

using namespace std;

// check if three given points are in counterclockwise order.
template<typename T>
bool ccw(const Point2D<T>& A, const Point2D<T>& B, const Point2D<T>& C) {
    return (C.y() - A.y()) * (B.x() - A.x()) > (B.y() - A.y()) * (C.x() - A.x());
}

// uses the ccw to check if two line segments AB and CD intersects
template<typename T>
bool intersect(const Point2D<T>& A, const Point2D<T>& B, const Point2D<T>& C, const Point2D<T>& D) {
    return ccw(A, C, D) != ccw(B, C, D) && ccw(A, B, C) != ccw(A, B, D);
}

/* 
 * Calculates the distance between point p and the line segment given by s1 and s2.
 * 
 * @param p The point to compute the distance from.
 * @param s1, s2 Two points that forms a line segment.
 */
template<typename T>
double point_segment_dist(const Point2D<T>& p, const Point2D<T> s1, const Point2D<T> s2) {
    Point2D<T> v = s2 - s1;
    Point2D<T> w = p - s1;

    T dot = w.x() * v.x() + w.y() * v.y();
    T len = v.magnitude() * v.magnitude();

    if(dot <= 0) {
        return w.magnitude();
    } else if(dot >= len) {
        return (p - s2).magnitude();
    } else {
        T t = dot / len;
        Point2D<T> proj = s1 + v * t;
        return (p - proj).magnitude();
    }
}

/* 
 * Finds the minimum distance between two line segments.
 * 
 * @param p1, p2 Two points that forms one line segment.
 * @param p3, p4 Two points that forms second line segment.
 * 
 * If the line segments intersect we know that the minimum distance is 0.0
 */
template<typename T>
double segment_distance(const Point2D<T>& p1, const Point2D<T>& p2, const Point2D<T>& p3, const Point2D<T>& p4) {
    if(intersect(p1, p2, p3, p4)) return 0.0;
    double dist1 = point_segment_dist(p1, p3, p4);
    double dist2 = point_segment_dist(p2, p3, p4);
    double dist3 = point_segment_dist(p3, p1, p2);
    double dist4 = point_segment_dist(p4, p1, p2);
    cout << dist1 <<"2 " << dist2 <<"3 " << dist3 << "4 " << dist4 << endl;
    // Return the minimum distance
    return min(min(dist1, dist2), min(dist3, dist4));
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        Point2D<double> p1(x1, y1);
        Point2D<double> p2(x2, y2);
        Point2D<double> p3(x3, y3);
        Point2D<double> p4(x4, y4);
        cout << fixed << setprecision(2) << segment_distance(p1, p2, p3, p4) << endl;
    }
    return 0;
}