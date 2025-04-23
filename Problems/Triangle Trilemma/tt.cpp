/*
    Author: William Sid (wilsi748)

    Problem solved: Triangle Trilemma
*/
#include <bits/stdc++.h>

using namespace std;

struct Point
{
    int x, y;
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cout << "Case #" << i+1 << ": ";
        Point p1, p2, p3; 
        cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
        // check if triangle
        if(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y) == 0) {
            cout << "not a triangle" << endl;
            continue;
        }
        // distances
        double p1p2 = ((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
        double p1p3 = ((p3.x - p1.x) * (p3.x - p1.x) + (p3.y - p1.y) * (p3.y - p1.y));
        double p2p3 = ((p3.x - p2.x) * (p3.x - p2.x) + (p3.y - p2.y) * (p3.y - p2.y));
        // check if isosceles or scalene
        if(p1p2 == p1p3 || p1p3 == p2p3 || p1p2 == p2p3) {
            cout << "isosceles ";
        } else {
            cout << "scalene ";
        }
        // check if the triangle is acute, right, or obtuse
        double sides[] = { p1p2, p1p3, p2p3 };
        sort(sides, sides+3);
        if(abs(sides[0] + sides[1] - sides[2]) <= 1e-9) {
            cout << "right ";
        } else if(sides[0] + sides[1] < sides[2]) {
            cout << "obtuse ";
        } else {
            cout << "acute ";
        }
        cout << "triangle" << endl;
    }
    return 0;
}