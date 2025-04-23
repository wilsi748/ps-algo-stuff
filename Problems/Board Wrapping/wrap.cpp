/*
    Author: William Sid (wilsi748)

    Problem solved: Board Wrapping
*/
#include <bits/stdc++.h>

using namespace std;

#define M_PI 3.14159265358979323846

// cross product of two complex vectors
double direction(complex<double> a, complex<double> b, complex<double> c) {
    return (b.real() - a.real()) * (c.imag() - a.imag()) - (b.imag() - a.imag()) * (c.real() - a.real());
}

void print_corners(vector<complex<double>> corners) {
    for (auto corner : corners) {
        cout << "(" << corner.real() << ", " << corner.imag() << ")" << endl;
    }
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int tests;
    cin >> tests;
    while(tests--) {
        int n_boards;
        double b_area = 0;
        vector<complex<double>> corners;
        cin >> n_boards;
        while(n_boards--) {
            double x, y, w, h, v; // x, y, width, height, rotation angle
            cin >> x >> y >> w >> h >> v;
            b_area += w * h; // total area of all boards
            complex<double> center(x, y); // center point of the rectangle
            double r = -1 * v * M_PI / 180.0;
            complex<double> rotation(cos(r), sin(r)); // rotation vector
            // height and width of the rotated rectangle
            complex<double> height = (complex<double>(0, h) * rotation) / 2.0; 
            complex<double> width = (complex<double>(w, 0) * rotation) / 2.0;
            
            // get the four corners of the rotated rectangle
            for(auto& m : {height + width, height - width, -height + width, -height - width}) {
                corners.push_back(center + m);
            }
        }
        print_corners(corners);
        // Calculate the convex hull, using Gramham scan
        // sort corners 
        sort(corners.begin(), corners.end(), [](complex<double> c1, complex<double> c2) {
            return c1.real() < c2.real() || (c1.real() == c2.real() && c1.imag() < c2.imag());
        });
        // divide the corner points into upper and lower hulls
        // ensure tranversal in the correct direction.
        vector<complex<double>> upper, lower;
        for(complex<double> c : corners) {
            while(upper.size() > 1 && direction(upper[upper.size() - 2], upper[upper.size() - 1], c) >= 0) {
                upper.pop_back();
            }
            upper.push_back(c);
            while(lower.size() > 1 && direction(lower[lower.size() - 2], lower[lower.size() - 1], c) <= 0) {
                lower.pop_back();
            }
            lower.push_back(c);
        }
        // add lower and upper hulls together, creating the convex hull
        // first add lower, then skip first and last of upper, those points already exists in lower.
        vector<complex<double>> hull;
        for(complex<double> c : lower) {
            hull.push_back(c);
        }
        for (int i = upper.size() - 2; i >= 0; i--) {
            hull.push_back(upper[i]);
        }
        complex<double> a = hull[0];
        double area = 0;
        // iterate over hull but skip first and last since they are the same.
        for(auto iter = hull.begin() + 1; iter != hull.end() - 1; ++iter) {
            // a, b, c are the points to form a triangle.
            complex<double> b = *iter; 
            complex<double> c = *(iter + 1);
            // translate b, c to have a as origin.
            b -= a; 
            c -= a;
            // calculate the area using cross product -> signed area of parallelogram given by b and c
            // divide by 2 to get the area of the triangle.
            area += abs((b.real() * c.imag()) -(c.real() * b.imag())) / 2.0;
        }
        cout << fixed << setprecision(1) << b_area / area * 100 << " %" << endl;
    }


    return 0;
}