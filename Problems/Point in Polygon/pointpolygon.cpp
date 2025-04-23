/*
    Author: William Sid (wilsi748)

    Problem solved: Point in Polygon

    Description:
    This code solves the "Point in Polygon" problem. It determines whether a given point lies inside, on the boundary, or outside a polygon defined by its vertices.
    The function inside_poly is defined within the Point2D class.
    
    The Point2D class takes two numbers as x and y coordinates and has to be defined using a numeric datatype 
    indicating what type of values x and y is.

    Example: 
    int x = 5;
    int y = -3;
    Point<int> example_point(x, y);
    cout << example_point << endl; -> (5, -3)

    Time complexity: O(n) where n is the number of vertexes.
*/
#include <bits/stdc++.h>
#include "../Point2D.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n, m;
    while(cin >> n && n != 0) {
        vector<Point2D<int>> poly(n);
        int x, y;
        for(int i = 0; i < n; i++) {
            cin >> x >> y;
            Point2D<int> point(x, y);
            poly[i] = point;
        }
        cin >> m;
        for(int i = 0; i < m; i++) {
            cin >> x >> y;
            Point2D<int> point(x, y);
            int res = inside_poly(point, poly);
            if (res == 0) {
                cout << "on" << endl;
            } else if (res == 1) {
                cout << "in" << endl;
            } else {
                cout << "out" << endl;
            }
        }
    }
    return 0;
}