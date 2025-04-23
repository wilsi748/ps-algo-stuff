/*
    Author: William Sid (wilsi748)

    Problem solved: Convex Hull

    Time complexity: O(n log n) where n is the number of input points.

    the function uses a few help function such as unique and sort which both has the time complexity of O(n log n),
    the actual Graham scan algorithm has a time complexity of O(n) because each input is processed exactly once in the while loop,
    but because of the sorting and such the total time complexity is O(n log n).
*/
#include <bits/stdc++.h>
#include "../Point2D.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n;
    while(cin >> n && n != 0) {
        vector<Point2D<int>> points;
        vector<Point2D<int>> hull;
        for(int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            Point2D<int> p(x, y);
            points.push_back(p);
        }
        hull = convex_hull(points);
        cout << hull.size() << endl;
        for(int i = 0; i < hull.size(); i++) {
            cout << hull[i].x() << " " << hull[i].y() << endl;
        }
    }
    return 0;
}