/*
    Author: William Sid (wilsi748)

    Problem solved: Line Segment Interaction

    Solved by calculating the determinant of the given by the system of linear equations formed by the two lines.
    If the determinant is 0 we know that the lines are parallel or collinear so we check if collinear.
    If the are collinear we check if the overlap, if they overlap we take endpoints of the intersecting line.
    If determinant is not 0 we calculate t1 and t2 using the Cramer's rule and check if t1 and t2 make a valid intersection point.

    Time complexity: O(n) where n is the number of points.
*/

#include <bits/stdc++.h>
#include "../Point2D.h"

using namespace std;

const double eps = 1e-9;

template <typename T>
struct Segment
{
    Point2D<T> p1, p2;
};

template <typename T>
bool segments_overlap(const Segment<T> &s1, const Segment<T> &s2)
{
    Point2D<T> v1 = s1.p2 - s1.p1;
    Point2D<T> v2 = s2.p2 - s2.p1;
    T cp1 = (s2.p1 - s1.p1) ^ v1;
    T cp2 = (s2.p2 - s1.p1) ^ v1;

    // check if the endpoints of s2 are on the same side of s1
    if (cp1 * cp2 > 0)
        return false;

    T cp3 = (s1.p1 - s2.p1) ^ v2;
    T cp4 = (s1.p2 - s2.p1) ^ v2;

    // check if the endpoints of s1 are on the same side of s2
    if (cp3 * cp4 > 0)
        return false;

    // check if s1 and s2 are collinear and overlapping
    if (cp1 == 0 && cp2 == 0 && cp3 == 0 && cp4 == 0)
    {
        // check if the bounding boxes overlap
        if (max(s1.p1.x(), s1.p2.x()) < min(s2.p1.x(), s2.p2.x()) ||
            max(s2.p1.x(), s2.p2.x()) < min(s1.p1.x(), s1.p2.x()) ||
            max(s1.p1.y(), s1.p2.y()) < min(s2.p1.y(), s2.p2.y()) ||
            max(s2.p1.y(), s2.p2.y()) < min(s1.p1.y(), s1.p2.y()))
        {
            return false;
        }
    }
    return true;
}




template <typename T>
vector<Point2D<double>> intersection(const Segment<T> &s1, const Segment<T> &s2)
{
    vector<Point2D<double>> res;
    double a1 = s1.p1.x(), b1 = s1.p1.y(), c1 = s1.p2.x(), d1 = s1.p2.y();
    double a2 = s2.p1.x(), b2 = s2.p1.y(), c2 = s2.p2.x(), d2 = s2.p2.y();

    double det = (c1 - a1) * (d2 - b2) - (c2 - a2) * (d1 - b1);

    if (abs(det) < eps)
    {
        // check if the segments are collinear and overlap
        if (segments_overlap(s1, s2))
        {
            // compute the overlapping segment.
            double min_x = max(min(a1, c1), min(a2, c2));
            double max_x = min(max(a1, c1), max(a2, c2));
            double min_y = max(min(b1, d1), min(b2, d2));
            double max_y = min(max(b1, d1), max(b2, d2));

            if (min_x <= max_x && min_y <= max_y)
            {
                Point2D<double> p1(min_x, min_y);
                Point2D<double> p2(max_x, max_y);
                if (p1 == p2)
                {
                    res.push_back(p1);
                    return res;
                }
                res.push_back(p1);
                res.push_back(p2);
                return res;
            }
        }
        return res;
    }

    double t1 = ((a2 - a1) * (d2 - b2) - (c2 - a2) * (b2 - b1)) / det;
    double t2 = ((a2 - a1) * (d1 - b1) - (c1 - a1) * (b2 - b1)) / det;

    // check if there is a valid intersection point
    if (t1 < 0.0 || t1 > 1.0 || t2 < 0.0 || t2 > 1.0)
    {
        return res;
    }

    // compute the intersection point
    double x = a1 + t1 * (c1 - a1);
    double y = b1 + t1 * (d1 - b1);
    Point2D<double> intersection(x, y);
    res.push_back(intersection);
    return res;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    while (n--)
    {
        int x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        Point2D<int> p1(x1, y1), p2(x2, y2), p3(x3, y3), p4(x4, y4);
        Segment<int> s1, s2;
        s1.p1 = p1;
        s1.p2 = p2;
        s2.p1 = p3;
        s2.p2 = p4;
        vector<Point2D<double>> res = intersection(s1, s2);
        if (res.size() == 0)
        {
            cout << "none" << endl;
        }
        else if (res.size() == 1)
        {
            double x = (abs(res[0].x()) < 0.005) ? 0.00 : res[0].x();
            double y = (abs(res[0].y()) < 0.005) ? 0.00 : res[0].y();
            cout << fixed << setprecision(2) << x << " " << y << endl;
        }
        else
        {
            double x1 = (abs(res[0].x()) < 0.005) ? 0.00 : res[0].x();
            double y1 = (abs(res[0].y()) < 0.005) ? 0.00 : res[0].y();
            double x2 = (abs(res[1].x()) < 0.005) ? 0.00 : res[1].x();
            double y2 = (abs(res[1].y()) < 0.005) ? 0.00 : res[1].y();
            cout << fixed << setprecision(2) << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
        }
    }
    return 0;
}