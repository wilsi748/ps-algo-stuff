/*
    Author: William Sid (wilsi748)

    Problem solved: Maximum Number of Colinear Points

    Time complexity: O(n^2) where n is the number of points.

    The function uses a nested loop to iterate over points and then for each point it calculates the slope and updates counter.
    Then using a map we keep track of the slopes and depending on the number of points with a certain slope we know how many points are colinear.
*/

#include <bits/stdc++.h>
#include "../Point2D.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    while(cin >> n && n != 0) {
        vector<Point2D<int>> points(n);
        for(int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            Point2D<int> p(x, y);
            points[i] = p;
        }
        // calc max number of collinear points
        cout << number_of_colinear_points(points) << endl;
    }

    return 0;
}