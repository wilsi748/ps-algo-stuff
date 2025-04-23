/*
    author: William Sid (wilsi748)

    Problem solved: Polynomial Multiplication 2

    Time complexity: O(n log n) where n is the size of the polynomials, 
    -> fft O(n log n) and multiplication between two polynomials using point-value multiplication takes O(n) time.
*/
#include <bits/stdc++.h>

using namespace std;

const double PI = 3.14159265358979323846;

// Fourier transform that computes the DFT
// takes poly vector of complex<double> representing the polynomial to transform
// and a boolean to indicate whether or not the inverse should be applied.
void fft(vector<complex<double>> &poly, bool invert) {
    int n = poly.size();
    // check for the cpolyse of one coefficent
    if (n == 1) {
        return;
    }
    // right polynd left sides 
    vector<complex<double>> left(n / 2), right(n / 2);
    for (int i = 0; i < n / 2; i++) {
        left[i] = poly[2 * i]; // fill with even index
        right[i] = poly[2 * i + 1]; // fill with odd index
    }
    // recursively call fft with both halves.
    fft(left, invert);
    fft(right, invert);
    // angle rotation of the complex plane
    double angle = 2 * PI / n * (invert ? -1 : 1);
    complex<double> omega(1), omega_n(cos(angle), sin(angle));
    // The recursive calls are combined using the butterfly algorithm.
    // even indexed poly vector is set to the sum of the left and right halves and 
    // the odd are set to the difference multiplied by the complex exponential
    // a_k = a_even_k + omega^k_n * a_odd_k
    for (int i = 0; i < n / 2; i++) {
        poly[i] = left[i] + omega * right[i];
        poly[i + n / 2] = left[i] - omega * right[i];
        // the inverse case.
        if (invert) {
            poly[i] /= 2;
            poly[i + n / 2] /= 2;
        }
        // compute the powers of the prim root of unity.
        omega *= omega_n;
    }
}

// takes two vector representing the polynomials
vector<int> multiply_polynomials(const vector<int> &poly1, const vector<int> &poly2) {
    // calculate the n, which should be the smallest power of 2 of order
    // needed for the fft algorithm which requires that the vectors are of power of 2.
    int n = 1, order = poly1.size() + poly2.size() - 1;
    while (n < order) {
        n *= 2;
    }
    // init two complex vecotrs with the coefficients of polynomials.
    vector<complex<double>> fa(n), fb(n);
    for (int i = 0; i < poly1.size(); i++) {
        fa[i] = poly1[i];
    }
    for (int i = 0; i < poly2.size(); i++) {
        fb[i] = poly2[i];
    }
    // apply fft
    fft(fa, false);
    fft(fb, false);
    // multiply the results
    for (int i = 0; i < n; i++) {
        fa[i] = fa[i] * fb[i];
    }
    // apply the inverse, go back to time domain.
    fft(fa, true);
    // get the real numbers and round them to the nearest integer.
    vector<int> result(order);
    for (int i = 0; i < order; i++) {
        result[i] = (int) floor(fa[i].real() + 0.5);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        int n1, n2;
        cin >> n1;
        vector<int> poly1(n1 + 1);
        for (int i = 0; i <= n1; i++) {
            cin >> poly1[i];
        }
        cin >> n2;
        vector<int> poly2(n2 + 1);
        for (int i = 0; i <= n2; i++) {
            cin >> poly2[i];
        }
        vector<int> result = multiply_polynomials(poly1, poly2);
        int n3 = result.size() - 1;
        cout << n3 << endl;
        for (int i = 0; i <= n3; i++) {
            cout << result[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}