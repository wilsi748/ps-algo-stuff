/*
    Author: William Sid (wilsi748)

    Problem solved: Polygon Area

    Description:
    Calculates the area of a polygon defined by a set of 2D points using the Point2D class.
    Then using the function called polygon_area inside the Point2D class calculate the area of a simple polygon with
    the Shoelace formula, also known as Gauss's area formula.
    The Shoelace formula calculates the signed area of a polygon by summing the products
    of consecutive coordinates of the polygon's vertices.
    An assumption is made that the points are given in counterclockwise order.
    This gives the information that if computed area is positive, it indicates counterclockwise orientation (CCW),
    while a negative area indicates clockwise orientation (CW).

    The Point2D class takes two numbers as x and y coordinates and has to be defined using a numeric datatype 
    indicating what type of values x and y is.

    Example: 
    int x = 5;
    int y = -3;
    Point<int> example_point(x, y);
    cout << example_point << endl; -> (5, -3)

    Time complexity: O(n), where n is the number of points in the polygon.
*/

#include <bits/stdc++.h>
#include "../Point2D.h"

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n;
    while (cin >> n && n != 0)
    {
        vector<Point2D<double>> points(n);
        for(int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            Point2D<double> p(x, y);
            points[i] = p;
        }
        // check if area is pos or neg to determine order.
        if(polygon_area(points) > 0) {
            // counterclockwise
            cout << fixed << setprecision(1) << "CCW " << abs(polygon_area(points)) << endl;
        } else {
            // clockwise
            cout << fixed << setprecision(1) << "CW " << abs(polygon_area(points)) << endl;
        }
    }
    return 0;
}
